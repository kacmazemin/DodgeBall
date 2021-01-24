//
// Created by emin on 23.01.2021.
//

#include "GameLayer.h"
#include "Utils/ScreenUtils.h"
#include "Physics/PhysicsManager.h"
#include "GameComponents/Ball.h"

cocos2d::Scene *GameLayer::createScene()
{
    return GameLayer::create();
}

bool GameLayer::init()
{
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    physicsManager = std::make_unique<PhysicsManager>();

    createBoundaries();

    createBalls();

    scheduleUpdate();

    return true;
}

void GameLayer::update(float dt)
{
    physicsManager->Update();
}

void GameLayer::RenderDebug()
{
    physicsManager->renderDebug();
}

void GameLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    cocos2d::Scene::draw(renderer, transform, flags);

    cocos2d::Director* director =  cocos2d::Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
    RenderDebug();
    CHECK_GL_ERROR_DEBUG();

    director->popMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

void GameLayer::createBoundaries()
{
    const float offsetX = ScreenUtils::getVisibleRect().size.width * .05f;
    const float offsetY = ScreenUtils::getVisibleRect().size.height * .05f;

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner

    b2Body* groundBody = physicsManager->GetWorld()->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;

    // bottom
    groundBox.Set(b2Vec2((ScreenUtils::leftBottom().x + offsetX) / PTM_RATIO, (ScreenUtils::leftBottom().y + offsetY) / PTM_RATIO),
                  b2Vec2((ScreenUtils::rightBottom().x - offsetX) / PTM_RATIO, (ScreenUtils::rightBottom().y + offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // top
    groundBox.Set(b2Vec2((ScreenUtils::leftTop().x + offsetX) / PTM_RATIO, (ScreenUtils::leftTop().y - offsetY) / PTM_RATIO),
                  b2Vec2((ScreenUtils::rightTop().x - offsetX) / PTM_RATIO, (ScreenUtils::rightTop().y - offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // left
    groundBox.Set(b2Vec2((ScreenUtils::leftTop().x + offsetX) / PTM_RATIO, (ScreenUtils::leftTop().y - offsetY) / PTM_RATIO),
                  b2Vec2((ScreenUtils::leftBottom().x + offsetX) / PTM_RATIO, (ScreenUtils::leftBottom().y + offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);

    // right
    groundBox.Set(b2Vec2((ScreenUtils::rightBottom().x - offsetX) / PTM_RATIO, (ScreenUtils::rightBottom().y + offsetY) / PTM_RATIO),
                  b2Vec2((ScreenUtils::rightTop().x - offsetX ) / PTM_RATIO, (ScreenUtils::rightTop().y - offsetY) / PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void GameLayer::createBalls()
{
    const cocos2d::Size size = ScreenUtils::getVisibleRect().size;
    const float startX = ScreenUtils::center().x - size.width * .1f;
    float startY = ScreenUtils::center().y;
    cocos2d::Vec2 pos = cocos2d::Vec2::ZERO;

    //pyramid positioning logic
    for (int i = 0; i < 5 ; i++)
    {
        for(int j = 0; j < i + 1; j++)
        {
            pos.x = startX - (BALL_RADIUS * 2) * i;
            pos.y = startY - ((BALL_RADIUS * 2) * j);
            Ball* ball = new Ball(*physicsManager->GetWorld(), pos);
            addChild(ball);
        }

        startY = startY + (BALL_RADIUS);
    }

}
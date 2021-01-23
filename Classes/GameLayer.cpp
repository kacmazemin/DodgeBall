//
// Created by emin on 23.01.2021.
//

#include "GameLayer.h"
#include "Utils/ScreenUtils.h"
#include "Box2D/Box2D.h"

#define SCALE_RATIO 32

cocos2d::Scene *GameLayer::createScene()
{
    return GameLayer::create();
}

bool GameLayer::init()
{
    // 1. super init first
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    cocos2d::Sprite* sprite = cocos2d::Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

    sprite->setPosition(ScreenUtils::leftTop());

    this->addChild(sprite, 0);


    world = new b2World(gravity);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    //flags +=b2Draw::e_aabbBit;
    flags += b2Draw::e_centerOfMassBit;

    if(!debugDraw)
    {
        debugDraw = new GLESDebugDraw(SCALE_RATIO);
        debugDraw->AppendFlags(flags);
    }

    world->SetDebugDraw(debugDraw);

    {
        cocos2d::Vec2 pos(cocos2d::Director::getInstance()->getWinSize().width / 2 - 150, cocos2d::Director::getInstance()->getWinSize().height / 2);
        cocos2d::Vec2 pos2(cocos2d::Director::getInstance()->getWinSize().width / 2 + 150, cocos2d::Director::getInstance()->getWinSize().height / 2);

        b2BodyDef bodyDef;
        bodyDef.fixedRotation = true;
        bodyDef.type = b2_dynamicBody;
        body = world->CreateBody(&bodyDef);
        body->SetGravityScale(2);
        body->SetTransform(b2Vec2(pos.x / SCALE_RATIO, pos.y / SCALE_RATIO), body->GetAngle());

        body2 = world->CreateBody(&bodyDef);
        body2->SetGravityScale(2);
        body2->SetTransform(b2Vec2(pos2.x / SCALE_RATIO, pos2.y / SCALE_RATIO), body->GetAngle());

        cocos2d::Vec2 size = cocos2d::Vec2(50, 50);
        b2FixtureDef fixDef;
        b2CircleShape shape;
        fixDef.restitution = 0.2f;
        fixDef.shape = &shape;
        shape.m_radius = 1;
//        shape.SetAsBox(size.x / SCALE_RATIO, size.y / SCALE_RATIO);

        fixDef.restitution = 1.0f;

        body->CreateFixture(&fixDef);

        body2->CreateFixture(&fixDef);
    }

    {
        cocos2d::Vec2 pos(ScreenUtils::bottom().x,
                          ScreenUtils::bottom().y);
        b2BodyDef bodyDef;
        bodyDef.fixedRotation = true;
        bodyDef.type = b2_staticBody;

        groundBody = world->CreateBody(&bodyDef);
        groundBody->SetTransform(b2Vec2(pos.x / SCALE_RATIO, pos.y / SCALE_RATIO), groundBody->GetAngle());

        cocos2d::Vec2 size = cocos2d::Vec2(ScreenUtils::getVisibleRect().size.width, 10);
        b2FixtureDef fixDef;
        b2PolygonShape shape;
        fixDef.restitution = 0.2f;
        fixDef.shape = &shape;
        shape.SetAsBox(size.x / SCALE_RATIO, size.y / SCALE_RATIO);

        groundBody->CreateFixture(&fixDef);
    }

    scheduleUpdate();

    return true;
}

void GameLayer::update(float dt)
{
    int positionIterations = 5;
    int velocityIterations = 1;

    world->Step(1.0 / 60.0, velocityIterations, positionIterations);

    for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
    {
        if (body->GetUserData() != nullptr)
        {
        }
    }
}

void GameLayer::RenderDebug()
{
    world->DrawDebugData();
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

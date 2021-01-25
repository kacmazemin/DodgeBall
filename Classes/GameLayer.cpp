//
// Created by emin on 23.01.2021.
//

#include "GameLayer.h"
#include "Utils/ScreenUtils.h"
#include "Physics/PhysicsManager.h"
#include "GameComponents/Ball.h"
#include "GameComponents/BilliardCue.h"
#include "GameComponents/GhostCue.h"
#include <ui/UIButton.h>

namespace
{
    constexpr int resetCueActionTagNo= 565;
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

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

    createTouchListener();

    physicsManager = std::make_unique<PhysicsManager>();
    createBoundaries();
    createBalls();
    createCue();

    createButton();
    scheduleUpdate();

    return true;
}

void GameLayer::createTouchListener()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameLayer::update(float dt)
{
    physicsManager->Update();

    if(playerBall)
    {
        canManipulateCue = !playerBall->isAwake();
    }

    if(canManipulateCue && isBallMoving)
    {
        resetCue();
        isBallMoving = false;
    }

    if(cue)
    {
        CCLOG("WORKWORKWORK VISIBILITY %i", cue->isVisible());
    }
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

void GameLayer::createCue()
{
    const cocos2d::Size size = ScreenUtils::getVisibleRect().size;
    const cocos2d::Vec2 ballPos = cocos2d::Vec2{ScreenUtils::center().x + size.width * .2f, ScreenUtils::center().y};
    const cocos2d::Vec2 cuePos = cocos2d::Vec2{ballPos.x + size.width * .1f + BALL_RADIUS * 11, ballPos.y };

    playerBall = new Ball(*physicsManager->GetWorld(), ballPos, true);
    addChild(playerBall);

    ghostCue = new GhostCue();
    ghostCue->setPosition(ballPos);

    addChild(ghostCue);

    cue = new BilliardCue(*physicsManager->GetWorld(), cuePos);
    cue->setVisible(false);
    addChild(cue);
}

void GameLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    cocos2d::Scene::draw(renderer, transform, flags);

    cocos2d::Director* director =  cocos2d::Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
    physicsManager->renderDebug();
    CHECK_GL_ERROR_DEBUG();

    director->popMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

bool GameLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    startLocation = touch->getStartLocation();
    firstLocation = cue->getPosition();

    auto diff = playerBall->getPosition() - touch->getLocation();
    previousAngle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    cocos2d::Vec2 currentLocation = touch->getLocation();

    if(canManipulateCue && ghostCue)
    {
        auto diff = ghostCue->getPosition() - touch->getLocation();
        auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
        ghostCue->setRotation(ghostCue->getRotation() + (angle - previousAngle));
        previousAngle = angle;

        cue->applyNewTransform(b2Vec2(ghostCue->getPos().x / PTM_RATIO, ghostCue->getPos().y / PTM_RATIO), CC_DEGREES_TO_RADIANS(-ghostCue->getRotation()));
    }
}

void GameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{

}

void GameLayer::createButton()
{
    auto button = cocos2d::ui::Button::create("button-normal.png", "button-clicked.png", "button-clicked.png");

    button->setTitleText("Button ");

    button->setPosition(cocos2d::Vec2{ScreenUtils::leftTop().x + button->getBoundingBox().size.width * .5f, ScreenUtils::leftTop().y - button->getBoundingBox().size.height * .5f});

    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                if(playerBall)
                {
                    isBallMoving = true;

                    ghostCue->setVisible(false);
                    cue->setVisible(true);
                    cue->applyForce();
                }
                break;
            default:
                break;
        }
    });

    this->addChild(button);
}

void GameLayer::resetCue()
{
    if(ghostCue && cue)
    {
        ghostCue->setPosition(playerBall->getPosition());
        ghostCue->setVisible(true);
        cue->applyNewTransform(b2Vec2(ghostCue->getPos().x / PTM_RATIO, ghostCue->getPos().y / PTM_RATIO), CC_DEGREES_TO_RADIANS(-ghostCue->getRotation()));
        cue->reset();
        cue->setVisible(false);
        isBallMoving = false;
    }
}

void GameLayer::fireCue()
{
    if(playerBall && cue)
    {
        cue->applyForce();
        ghostCue->setPosition(playerBall->getPosition());
    }
}
//
// Created by emin on 23.01.2021.
//

#include "GameLayer.h"
#include "Utils/ScreenUtils.h"
#include "Physics/PhysicsManager.h"
#include "Physics/SpriteWithPhysics.h"
#include "GameComponents/Ball.h"
#include "GameComponents/BilliardCue.h"
#include "GameComponents/GhostCue.h"
#include "GameComponents/Pocket.h"
#include "GameComponents/Board.h"
#include <ui/UIButton.h>

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
    _eventDispatcher->removeEventListener(onPlayerBallAndPocketCollided);
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
    createBoard();
    createBalls();
    createCueAndPlayerBall();

    createButton();
    createCustomEventListener();
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

    if(canManipulateCue && isBallMoving && !isPlayerBallFail)
    {
        resetCue();
        isBallMoving = false;
    }

}

void GameLayer::createBoard()
{
    board = new Board(*physicsManager->GetWorld());
    board->setPosition(ScreenUtils::center());
    board->changePhysicsPosition(ScreenUtils::center());
    addChild(board);
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

            gameBalls.emplace_back(ball);
        }

        startY = startY + (BALL_RADIUS);
    }

}

void GameLayer::createCueAndPlayerBall()
{
    const cocos2d::Size size = ScreenUtils::getVisibleRect().size;
    const auto boardBB = cocos2d::utils::getCascadeBoundingBox(board);
    playerBallInitPosition = {boardBB.getMidX() + boardBB.size.width * .25f, boardBB.getMidY()};
    const cocos2d::Vec2 cuePos = {playerBallInitPosition.x + size.width * .1f + BALL_RADIUS * 11, playerBallInitPosition.y };


    playerBall = new Ball(*physicsManager->GetWorld(), playerBallInitPosition, true);
    addChild(playerBall);


    ghostCue = new GhostCue();
    ghostCue->setPosition(playerBallInitPosition);

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
    auto diff = playerBall->getPosition() - touch->getLocation();
    previousAngle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    cocos2d::Vec2 currentLocation = touch->getLocation();

    if(canManipulateCue && ghostCue && !isPlayerBallFail)
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
                if(playerBall && !isBallMoving && !isPlayerBallFail)
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

    auto resetButton = cocos2d::ui::Button::create("button-normal.png", "button-clicked.png", "button-clicked.png");

    resetButton->setTitleText("RESET");

    resetButton->setPosition(cocos2d::Vec2{button->getPositionX(), button->getBoundingBox().getMinY() - button->getBoundingBox().size.height});

    resetButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::ENDED:
                restartGame();
                break;
            default:
                break;
        }
    });

    this->addChild(resetButton);
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
        isPlayerBallFail = false;
    }
}

void GameLayer::createCustomEventListener()
{
    onPlayerBallAndPocketCollided = cocos2d::EventListenerCustom::create("onPlayerBallAndPocketCollided",
    [=](cocos2d::EventCustom* event)
    {
        isPlayerBallFail = true;

        runAction(cocos2d::Sequence::create({
                cocos2d::DelayTime::create(2.2f),
                cocos2d::CallFunc::create([=]()
                {
                    isBallMoving = false;

                    const cocos2d::Size size = ScreenUtils::getVisibleRect().size;
                    const cocos2d::Vec2 ballPos = cocos2d::Vec2{
                            ScreenUtils::center().x +
                            size.width * .2f,
                            ScreenUtils::center().y};

                    ghostCue->setVisible(false);
                    cue->setVisible(false);

                    playerBall->setVisible(true);
                    playerBall->setBodyPosition(ballPos);

                }),
                cocos2d::DelayTime::create(1.5f),
                cocos2d::CallFunc::create([=]()
                {
                    resetCue();
                })
        }));
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(onPlayerBallAndPocketCollided, this);
}

void GameLayer::restartGame()
{
    for (const auto& ball : gameBalls)
    {
        ball->reset();
        ball->setVisible(true);
    }

    playerBall->setPosition(playerBallInitPosition);
    playerBall->reset();
    resetCue();
}
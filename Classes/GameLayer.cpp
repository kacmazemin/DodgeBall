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
#include "UI/CuePanel.h"
#include "UI/LoadingNode.h"
#include "UI/BallChartNode.h"
#include "UI/RemainingShootNode.h"
#include "UI/AnnouncerNode.h"
#include "UI/CustomButton.h"
#include "UI/PopupInGame.h"
#include "MenuScene.h"
#include "AudioManager.h"

namespace
{
    constexpr int attemptCount = 5;
    constexpr int popupZOrder = 10;
}

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{
    _eventDispatcher->removeEventListener(onPlayerBallAndPocketCollided);
    _eventDispatcher->removeEventListener(onCueHitPlayerBall);
    _eventDispatcher->removeEventListener(onBallHitPocket);
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

    physicsManager = std::make_unique<PhysicsManager>();

    createTouchListener();

    createBackground();
    createBoard();
    createBalls();
    createCuePanel();
    createLoadingNode();
    createMenuButton();
    createFireButton();
    createCueAndPlayerBall();
    createBallChartNode();
    createRemainingShootNode();
    createAnnouncerNode();

    createCustomEventListener();
    scheduleUpdate();

    AudioManager::getInstance()->playGamePlayMusic();

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

    if(canManipulateCue && isCueFired && !isPlayerBallFail)
    {
        resetCue();
    }

}

void GameLayer::createBackground()
{
    background = cocos2d::Sprite::create("textures/gameplay-bg.jpg");
    ScreenUtils::fitWH(background, ScreenUtils::getVisibleRect().size.width,
                       ScreenUtils::getVisibleRect().size.height);
    background->setPosition(ScreenUtils::center());

    addChild(background);
}

void GameLayer::createBoard()
{
    board = new Board(*physicsManager->GetWorld());
    board->setPosition(ScreenUtils::center());
    board->changePhysicsPosition(ScreenUtils::center());
    addChild(board);

    boardRect = cocos2d::utils::getCascadeBoundingBox(board);
}

void GameLayer::createBalls()
{
    const cocos2d::Size size = ScreenUtils::getVisibleRect().size;
    const float startX = ScreenUtils::center().x - size.width * .1f;
    float startY = ScreenUtils::center().y;
    cocos2d::Vec2 pos = cocos2d::Vec2::ZERO;

    int id = 0;
    //pyramid positioning logic
    for (int i = 0; i < 5 ; i++)
    {
        for(int j = 0; j < i + 1; j++)
        {
            id++;
            pos.x = startX - (BALL_RADIUS * 2) * i;
            pos.y = startY - (BALL_RADIUS * 2) * j;

            Ball* ball = new Ball(*physicsManager->GetWorld(), pos, id);
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

    playerBall = new Ball(*physicsManager->GetWorld(), playerBallInitPosition, 0, true);

    ghostCue = new GhostCue();
    ghostCue->setPosition(playerBallInitPosition);

    cue = new BilliardCue(*physicsManager->GetWorld(), ghostCue->getSpritePosition());
    cue->setVisible(false);

    addChild(playerBall,1);
    addChild(ghostCue, 1);
    addChild(cue, 1);
}

void GameLayer::createCuePanel()
{
    const float desiredWidth = (ScreenUtils::getVisibleRect().size.width - boardRect.size.width) * .25f;

    cuePanel = new CuePanel({desiredWidth, boardRect.size.height * .7f});

    const cocos2d::Size panelSize = cocos2d::utils::getCascadeBoundingBox(cuePanel).size;

    cuePanel->setRotation(-90);

    cuePanel->setPosition(ScreenUtils::left().x + desiredWidth, ScreenUtils::center().y + panelSize.height * .2f);
    addChild(cuePanel);

}

void GameLayer::createBallChartNode()
{
    const float desiredHeight = ScreenUtils::top().y - boardRect.getMaxY();

    ballChartNode = new BallChartNode(desiredHeight, gameBalls.size());
    ballChartNode->setPosition(ScreenUtils::top());
    addChild(ballChartNode);
}

void GameLayer::createRemainingShootNode()
{
    const float desiredHeight = boardRect.getMinY() - ScreenUtils::bottom().y;

    remainingShootNode = new RemainingShootNode(desiredHeight, 5);
    remainingShootNode->setPosition(ScreenUtils::bottom());
    addChild(remainingShootNode);
}

void GameLayer::createAnnouncerNode()
{
    announcerNode = new AnnouncerNode();
    announcerNode->setPositionX(ScreenUtils::center().x);
    announcerNode->setPositionY(ScreenUtils::center().y + ScreenUtils::getVisibleRect().size.height * .2f);
    addChild(announcerNode, 2);
}

void GameLayer::createLoadingNode()
{
    loadingNode = new LoadingNode(ScreenUtils::getVisibleRect().size * .15f);
    addChild(loadingNode);

    const cocos2d::Size loadingNodeSize = cocos2d::utils::getCascadeBoundingBox(loadingNode).size;
    loadingNode->setPositionX(cuePanel->getPositionX());
    loadingNode->setPositionY(ScreenUtils::leftTop().y - loadingNodeSize.height * .5f);

    loadingNode->setVisible(false);

}

void GameLayer::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
    cocos2d::Scene::draw(renderer, transform, flags);

    cocos2d::Director* director =  cocos2d::Director::getInstance();
    CCASSERT(nullptr != director, "Director is null when seting matrix stack");
    director->pushMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix( cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

    cocos2d::GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
//    physicsManager->renderDebug();
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

void GameLayer::createMenuButton()
{
    menuButton = new CustomButton("textures/menu-button-in-game.png", ScreenUtils::getVisibleRect().size * .2f);

    menuButton->setPosition(ScreenUtils::rightTop() - menuButton->getBoundingBox().size * .65f);

    menuButton->setOnTap([=]()
    {
        showExitGamePopup();
    });

    addChild(menuButton);
}

void GameLayer::createFireButton()
{
    auto button = new CustomButton("textures/fire-button.png", ScreenUtils::getVisibleRect().size * .2f);

    if(cuePanel)
    {
        const auto cuePanelBB = cocos2d::utils::getCascadeBoundingBox(cuePanel);
        button->setPositionX(cuePanel->getPositionX());
        button->setPositionY(cuePanelBB.getMinY() - button->getBoundingBox().size.height * .6f);

    }

    button->setOnTap([=](){
        if(!isCueFired && !isPlayerBallFail && canManipulateCue)
        {
            if(cuePanel)
            {
                cuePanel->changeActivity(false);
            }

            if(loadingNode)
            {
                loadingNode->setVisible(true);
            }

            ghostCue->setVisible(false);
            cue->setVisible(true);
            cue->applyForce(cuePanel->getPowerFromBar());
        }
    });
    button->enableTintTo();

    addChild(button);
}

void GameLayer::resetCue()
{
    if(ghostCue && cue)
    {
        ghostCue->setPosition(playerBall->getPosition());
        ghostCue->setVisible(true);
        cue->applyNewTransform(b2Vec2(ghostCue->getPos().x / PTM_RATIO, ghostCue->getPos().y / PTM_RATIO),
                CC_DEGREES_TO_RADIANS(-ghostCue->getRotation()));
        cue->reset();
        cue->setVisible(false);
        isCueFired = false;
        isPlayerBallFail = false;

        if(loadingNode)
        {
            loadingNode->setVisible(false);
        }

        if(cuePanel)
        {
            cuePanel->changeActivity(true);
        }
    }
}

void GameLayer::handlePlayerBallFail()
{
    isPlayerBallFail = true;

    remainingAttempting--;

    if(remainingShootNode)
    {
        remainingShootNode->consumeSlot();
    }

    runAction(cocos2d::Sequence::create({
        cocos2d::DelayTime::create(2.2f),
        cocos2d::CallFunc::create([=]() {
            isCueFired = false;

            ghostCue->setVisible(false);
            cue->setVisible(false);

            playerBall->setVisible(true);
            playerBall->reset();
        }),
        cocos2d::DelayTime::create(1.5f),
        cocos2d::CallFunc::create([=]() {
            resetCue();
        })
    }));
}


void GameLayer::createCustomEventListener()
{
    onPlayerBallAndPocketCollided = cocos2d::EventListenerCustom::create("onPlayerBallAndPocketCollided",
    [=](cocos2d::EventCustom* event)
    {
        handlePlayerBallFail();

        if(announcerNode)
        {
            announcerNode->makeAnnounce(AnnounceType::Fail);
        }
        checkMatchSituation();
    });

    onCueHitPlayerBall = cocos2d::EventListenerCustom::create("onCueHitPlayerBall",
    [=](cocos2d::EventCustom* event)
    {
        isCueFired = true;
    });

    onBallHitPocket = cocos2d::EventListenerCustom::create("onBallHitPocket",
    [=](cocos2d::EventCustom* event)
    {
        if(ballChartNode)
        {
            ballChartNode->setCollected();

            if(announcerNode)
            {
                announcerNode->makeAnnounce(AnnounceType::Score);
            }
        }
        score++;
        checkMatchSituation();
    });

    _eventDispatcher->addEventListenerWithSceneGraphPriority(onPlayerBallAndPocketCollided, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onCueHitPlayerBall, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(onBallHitPocket, this);
}

void GameLayer::restartGame()
{
    remainingAttempting = attemptCount;

    for (const auto& ball : gameBalls)
    {
        ball->reset();
        ball->setVisible(true);
    }

    playerBall->setPosition(playerBallInitPosition);
    playerBall->reset();

    if(ballChartNode)
    {
        ballChartNode->reset();
    }

    if(remainingShootNode)
    {
        remainingShootNode->reset();
    }

    score = 0;
    resetCue();
}

void GameLayer::checkMatchSituation()
{
    if(score == gameBalls.size() || remainingAttempting == 0)
    {
        showInGamePopup();
    }
}

void GameLayer::showInGamePopup()
{
    auto* popup = new PopupInGame(true);

    popup->setYesOnTapFunction([=]()
    {
        restartGame();
    });

    popup->setNoOnTapFunction([=]()
    {
        auto scene = MenuScene::createScene();

        cocos2d::Director::getInstance()->runWithScene(scene);
    });

    popup->setPosition(ScreenUtils::center());

    addChild(popup, popupZOrder);
}

void GameLayer::showExitGamePopup()
{
    auto* popup = new PopupInGame(false);

    popup->setYesOnTapFunction([=]()
   {
       auto scene = MenuScene::createScene();

       cocos2d::Director::getInstance()->runWithScene(scene);
   });

    popup->setPosition(ScreenUtils::center());

    addChild(popup, popupZOrder);
}
//
// Created by emin on 23.01.2021.
//

#ifndef _GAMELAYER_H
#define _GAMELAYER_H

#include "cocos2d.h"

class PhysicsManager;
class BilliardCue;
class Ball;
class GhostCue;
class Board;
class CuePanel;
class LoadingNode;

class GameLayer : public cocos2d::Scene
{

public:
    GameLayer();
    ~GameLayer();

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameLayer);

private:

    bool canManipulateCue = true;
    bool isBallMoving = false;
    bool isPlayerBallFail = false;
    bool isA = true;
    float previousAngle = 0;

    cocos2d::Vec2 playerBallInitPosition = cocos2d::Vec2::ZERO;

    std::unique_ptr<PhysicsManager> physicsManager;

    BilliardCue* cue = nullptr;
    GhostCue* ghostCue = nullptr;
    Ball* playerBall = nullptr;
    Board* board = nullptr;
    CuePanel* cuePanel = nullptr;
    LoadingNode* loadingNode = nullptr;

    cocos2d::EventListenerCustom* onPlayerBallAndPocketCollided = nullptr;

    std::vector<Ball*> gameBalls;


    void createTouchListener();
    void createCustomEventListener();

    void update(float dt);

    void createBoard();
    void createBalls();
    void createCueAndPlayerBall();
    void createButton();
    void createCuePanel();
    void createLoadingNode();

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

    void resetCue();

    void restartGame();


};


#endif //_GAMELAYER_H

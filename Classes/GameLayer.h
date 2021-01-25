//
// Created by emin on 23.01.2021.
//

#ifndef _GAMELAYER_H
#define _GAMELAYER_H

#include "cocos2d.h"

#define PTM_RATIO 32

class PhysicsManager;
class BilliardCue;
class Ball;
class GhostCue;

class GameLayer : public cocos2d::Scene
{

public:
    GameLayer();
    ~GameLayer();

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameLayer);

private:

    cocos2d::Vec2 startLocation = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 firstLocation = cocos2d::Vec2::ZERO;

    bool canManipulateCue = true;
    bool isBallMoving = false;

    float previousAngle = 0;

    std::unique_ptr<PhysicsManager> physicsManager;

    BilliardCue* cue = nullptr;
    GhostCue* ghostCue = nullptr;
    Ball* playerBall = nullptr;

    void createTouchListener();

    void update(float dt);

    void createBoundaries();
    void createBalls();

    void createCue();

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

    virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
    virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);

    void createButton();

    void resetCue();
    void fireCue();

};


#endif //_GAMELAYER_H

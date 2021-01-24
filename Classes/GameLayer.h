//
// Created by emin on 23.01.2021.
//

#ifndef _GAMELAYER_H
#define _GAMELAYER_H

#include "cocos2d.h"

#define PTM_RATIO 32

class PhysicsManager;
class BilliardCue;

class GameLayer : public cocos2d::Scene
{

public:
    GameLayer();
    ~GameLayer();

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameLayer);

private:
    std::unique_ptr<PhysicsManager> physicsManager;

    BilliardCue* cue = nullptr;

    void createBoundaries();
    void createBalls();

    void createCue();

    void update(float dt);
    void RenderDebug();

    void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);

};


#endif //_GAMELAYER_H

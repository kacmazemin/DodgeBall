//
// Created by emin on 24.01.2021.
//

#ifndef PROJ_ANDROID_BALL_H
#define PROJ_ANDROID_BALL_H

#include "../Physics/SpriteWithPhysics.h"
#include "../Utils/ScreenUtils.h"

#define BALL_RADIUS ScreenUtils::getVisibleRect().size.height * .025f

class b2World;

class Ball : public SpriteWithPhysics
{
public:
    Ball(b2World& world, const cocos2d::Vec2& startPos, const bool isPlayer = false);

    virtual void update (float dt);

private:
    b2World* world = nullptr;

    cocos2d::Vec2 startPos = cocos2d::Vec2::ZERO;

    void createBall();

};


#endif //PROJ_ANDROID_BALL_H

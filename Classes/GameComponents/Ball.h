//
// Created by emin on 24.01.2021.
//

#ifndef _BALL_H
#define _BALL_H

#include "../Physics/SpriteWithPhysics.h"
#include "../Utils/ScreenUtils.h"

#define BALL_RADIUS ScreenUtils::getVisibleRect().size.height * .025f

class b2World;
class b2Vec2;

class Ball : public SpriteWithPhysics
{
public:
    Ball(b2World& world, const cocos2d::Vec2& startPos, const int id, const bool isPlayer = false);

    virtual void update (float dt) override;

    b2Vec2 getBodyPos () const;

    bool isAwake() const;

    inline int getId() const
    {
        return id;
    }

    virtual void hide() override;
    virtual void reset() override;


private:
    int id = 0;
    bool isPlayerBall = false;
    b2World* world = nullptr;

    cocos2d::Vec2 startPos = cocos2d::Vec2::ZERO;

    void createBall(const bool isPlayerBall);

};


#endif //_BALL_H

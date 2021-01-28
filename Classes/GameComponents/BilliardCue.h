//
// Created by emin on 24.01.2021.
//

#ifndef _BILLIARDCUE_H
#define _BILLIARDCUE_H

#include "../Physics/SpriteWithPhysics.h"

class b2World;
class b2Vec2;

class BilliardCue : public SpriteWithPhysics
{
public:
    BilliardCue(b2World& world, const cocos2d::Vec2& startPos);
    ~BilliardCue();

    void applyForce(const float power);
    void applyNewTransform(const b2Vec2& position, const float angle);

    virtual void hide() override;
    virtual void reset() override;

private:
    b2World* world = nullptr;

    cocos2d::Vec2 startPos = cocos2d::Vec2::ZERO;

    void createCue();
};


#endif //_BILLIARDCUE_H

//
// Created by emin on 24.01.2021.
//

#ifndef _SPRITEWITHPHYSICS_H
#define _SPRITEWITHPHYSICS_H

#include <cocos/2d/CCSprite.h>

class b2World;
class b2Body;

namespace
{
    //do not use 0x0001 since the default category for a fixture is 1
    constexpr uint16_t playerBallCategoryBit = 0x0100;
    constexpr uint16_t ballCategoryBit = 0x0002;
}

enum class PhysicsType
{
    BALL,
    PLAYER_BALL,
    POCKET,
    TABLE_EDGES,
    CUE,
    UNDEFINED
};

class SpriteWithPhysics : public cocos2d::Sprite
{
public:
    SpriteWithPhysics();
    ~SpriteWithPhysics();

    b2Body* spriteBody = nullptr;
    const b2World* worldRef = nullptr;

    inline const PhysicsType getType() const
    {
        return type;
    }

    float getMagnitude() const;

    virtual void hide();
    virtual void reset();
    virtual void setBodyPosition (const cocos2d::Vec2& position);

protected:
    virtual void update(float dt);

    PhysicsType type = PhysicsType::UNDEFINED;
};


#endif //_SPRITEWITHPHYSICS_H

//
// Created by emin on 24.01.2021.
//

#ifndef _SPRITEWITHPHYSICS_H
#define _SPRITEWITHPHYSICS_H

#include <cocos/2d/CCSprite.h>

class b2World;
class b2Body;

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

protected:
    virtual void setBodyPosition (const cocos2d::Vec2& position);
    virtual void update(float dt);

    PhysicsType type = PhysicsType::UNDEFINED;
};


#endif //_SPRITEWITHPHYSICS_H

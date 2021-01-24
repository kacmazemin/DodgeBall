//
// Created by emin on 24.01.2021.
//

#ifndef _SPRITEWITHPHYSICS_H
#define _SPRITEWITHPHYSICS_H

#include <cocos/2d/CCSprite.h>

class b2World;
class b2Body;

class SpriteWithPhysics : public cocos2d::Sprite
{
public:
    SpriteWithPhysics(const b2World& world);
    ~SpriteWithPhysics();

    b2Body* spriteBody = nullptr;
    const b2World* worldRef = nullptr;

protected:
    virtual void setSpritePosition (const cocos2d::Vec2& position);
    virtual void update(float dt);
    virtual void hide();
    virtual void reset();

};


#endif //_SPRITEWITHPHYSICS_H

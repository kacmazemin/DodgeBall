//
// Created by emin on 24.01.2021.
//

#include "SpriteWithPhysics.h"
#include "Box2D/Dynamics/b2Body.h"
#include "../Utils/ScreenUtils.h"

SpriteWithPhysics::SpriteWithPhysics()
{
    scheduleUpdate();
}

SpriteWithPhysics::~SpriteWithPhysics()
{

}

void SpriteWithPhysics::update(float dt)
{
    if (spriteBody && isVisible())
    {
        setPositionX(spriteBody->GetPosition().x * PTM_RATIO);
        setPositionY(spriteBody->GetPosition().y * PTM_RATIO);
        setRotation(CC_RADIANS_TO_DEGREES(-1 * spriteBody->GetAngle()));
    }
}

void SpriteWithPhysics::setBodyPosition(const cocos2d::Vec2 &position)
{
    if (spriteBody)
    {
        spriteBody->SetTransform(b2Vec2( position.x / PTM_RATIO, position.y/ PTM_RATIO), spriteBody->GetAngle());
    }
}

void SpriteWithPhysics::hide()
{
    if (spriteBody)
    {
        spriteBody->SetLinearVelocity(b2Vec2_zero);
        spriteBody->SetAngularVelocity(0);
        spriteBody->SetTransform(b2Vec2_zero, 0.0);
        spriteBody->SetAwake(false);
    }
}

void SpriteWithPhysics::reset()
{
    spriteBody->SetAwake(true);
}

float SpriteWithPhysics::getMagnitude() const
{
    if (spriteBody)
    {
        return std::pow(spriteBody->GetLinearVelocity().x, 2) +
               std::pow(spriteBody->GetLinearVelocity().y, 2);
    }

    return .0f;
}
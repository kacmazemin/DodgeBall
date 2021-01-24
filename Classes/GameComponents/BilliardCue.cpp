//
// Created by emin on 24.01.2021.
//

#include "BilliardCue.h"

#include "../GameLayer.h"
#include "Ball.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "../Utils/ScreenUtils.h"

BilliardCue::BilliardCue(b2World& world, const cocos2d::Vec2& startPos) : world(&world), startPos(startPos)
{
    this->init();
    autorelease();

    createCue();
}

BilliardCue::~BilliardCue()
{

}

void BilliardCue::createCue()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    spriteBody = world->CreateBody(&bodyDef);
    spriteBody->SetSleepingAllowed(true);
    spriteBody->SetLinearDamping(8);
    spriteBody->SetAngularDamping(5);

    b2PolygonShape box;
    box.SetAsBox(BALL_RADIUS * 11 / PTM_RATIO, BALL_RADIUS * 0.2 / PTM_RATIO);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &box;
    //todo define maskBits and use it
    fixtureDef.filter.maskBits = 0x0100;
    fixtureDef.density = 10;
    fixtureDef.restitution = 1;
    spriteBody->CreateFixture(&fixtureDef);
    spriteBody->SetUserData(this);

    this->initWithFile("cue.png");

    setBodyPosition(startPos);

    setPositionX(spriteBody->GetPosition().x * PTM_RATIO);
    setPositionY(spriteBody->GetPosition().y * PTM_RATIO);

    ScreenUtils::fitW(this, BALL_RADIUS * 22);
}

void BilliardCue::applyForce()
{
    if(spriteBody)
    {
        const float angle = spriteBody->GetAngle();

        spriteBody->ApplyLinearImpulse(b2Vec2(-6 * cos(angle) * 100,  sin(angle) * 6 * 100), spriteBody->GetWorldCenter(), true);
    }
}

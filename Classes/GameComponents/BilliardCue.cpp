//
// Created by emin on 24.01.2021.
//

#include "BilliardCue.h"

#include "Ball.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "../Utils/ScreenUtils.h"
#include <math.h>

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
    type = PhysicsType::CUE;

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
    fixtureDef.filter.maskBits = playerBallCategoryBit;
    fixtureDef.density = 10;
    fixtureDef.restitution = 1;
    spriteBody->CreateFixture(&fixtureDef);
    spriteBody->SetUserData(this);

    this->initWithFile("textures/cue.png");

    setBodyPosition(startPos);

    setPositionX(spriteBody->GetPosition().x * PTM_RATIO);
    setPositionY(spriteBody->GetPosition().y * PTM_RATIO);

    ScreenUtils::fitW(this, BALL_RADIUS * 22);
}

void BilliardCue::applyForce(const float power)
{
    if(spriteBody)
    {
        spriteBody->ApplyLinearImpulse(-b2Vec2(cos(spriteBody->GetAngle()) * power,
                sin(spriteBody->GetAngle()) * power ),spriteBody->GetWorldCenter(),true);
    }
}

void BilliardCue::applyNewTransform(const b2Vec2& position, const float angle)
{
    if(spriteBody)
    {
        spriteBody->SetAngularVelocity(0);
        spriteBody->SetTransform(position, angle);
    }
}

void BilliardCue::hide()
{
    runAction(cocos2d::Sequence::create({
        cocos2d::DelayTime::create(0.01f),
        cocos2d::CallFunc::create([=]()
        {
            if(spriteBody)
            {
                if(b2Fixture* bodyFixture = spriteBody->GetFixtureList())
                {
                    bodyFixture->SetSensor(true);
                }
            }
            SpriteWithPhysics::hide();
        })
    }));
}

void BilliardCue::reset()
{
    if(spriteBody)
    {
        if(b2Fixture* bodyFixture = spriteBody->GetFixtureList())
        {
            bodyFixture->SetSensor(false);

            b2Filter filter = bodyFixture->GetFilterData();
            filter.maskBits = playerBallCategoryBit;
            bodyFixture->SetFilterData(filter);
        }
    }
    SpriteWithPhysics::reset();
}

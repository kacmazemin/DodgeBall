//
// Created by emin on 24.01.2021.
//

#include "Ball.h"

#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"

Ball::Ball(b2World &world, const cocos2d::Vec2& startPos, const int id, const bool isPlayerBall)
: world(&world), startPos(startPos), id(id), isPlayerBall(isPlayerBall)
{
    this->init();
    autorelease();

    createBall(isPlayerBall);
}

void Ball::createBall(const bool isPlayerBall)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    spriteBody = this->world->CreateBody(&bodyDef);
    spriteBody->SetSleepingAllowed(true);
    spriteBody->SetLinearDamping(1.2);
    spriteBody->SetAngularDamping(0.8);

    //create  shape
    b2CircleShape circle;
    circle.m_radius =  BALL_RADIUS / PTM_RATIO;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0.7;

    this->initWithFile(cocos2d::StringUtils::format("textures/balls/ball-%d.png", id));

    if (isPlayerBall)
    {
        type = PhysicsType::PLAYER_BALL;
        spriteBody->SetBullet(true);
        fixtureDef.filter.categoryBits = playerBallCategoryBit;
    }
    else
    {
        type = PhysicsType::BALL;
        fixtureDef.filter.categoryBits = ballCategoryBit;
    }

    spriteBody->CreateFixture(&fixtureDef);
    spriteBody->SetUserData(this);

    ScreenUtils::fitH(this, BALL_RADIUS * 2.0f);

    setBodyPosition(startPos);
}

void Ball::update(float dt)
{
    if (spriteBody && isVisible()) {
        setPositionX(spriteBody->GetPosition().x * PTM_RATIO);
        setPositionY(spriteBody->GetPosition().y * PTM_RATIO);
        setRotation(spriteBody->GetAngle() * PTM_RATIO);
    }
}

b2Vec2 Ball::getBodyPos() const
{
    if(spriteBody)
    {
        return spriteBody->GetPosition();
    }
    return b2Vec2_zero;
}

bool Ball::isAwake() const
{
    if(spriteBody)
    {
        return spriteBody->IsAwake();
    }
    return false;
}

void Ball::hide()
{
    if(spriteBody)
    {
        if(b2Fixture* bodyFixture = spriteBody->GetFixtureList())
        {
            bodyFixture->SetSensor(true);
        }
    }

    setVisible(false);
    SpriteWithPhysics::hide();
}

void Ball::reset()
{
    if(spriteBody)
    {
        if(b2Fixture* bodyFixture = spriteBody->GetFixtureList())
        {
            bodyFixture->SetSensor(false);

            b2Filter filter = bodyFixture->GetFilterData();
            filter.categoryBits = isPlayerBall ? playerBallCategoryBit :  ballCategoryBit;
            bodyFixture->SetFilterData(filter);
        }
    }
    setBodyPosition(startPos);
    SpriteWithPhysics::reset();
}

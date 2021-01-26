//
// Created by emin on 26.01.2021.
//

#include "Pocket.h"
#include "Ball.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Fixture.h"

Pocket::Pocket(b2World& world, const cocos2d::Vec2& pos) : world(&world), pos(pos)
{
    this->init();
    autorelease();

    unscheduleUpdate();

    type = PhysicsType::POCKET;
    createBody();
}

Pocket::~Pocket()
{

}

void Pocket::createBody()
{
    b2BodyDef bodyDef;

    b2CircleShape circle;
    b2FixtureDef fixtureDef;

    bodyDef.type = b2_staticBody;
    spriteBody = world->CreateBody(&bodyDef);
    fixtureDef.isSensor = true;
    circle.m_radius = (float) (1.5 * BALL_RADIUS) / PTM_RATIO;
    fixtureDef.shape = &circle;
    spriteBody->CreateFixture(&fixtureDef);

    spriteBody->SetUserData(this);

    //added offset since b2body and cocos2dx origin is not same
    setBodyPosition(ScreenUtils::center() + pos);
}

void Pocket::addOffset(const cocos2d::Vec2& offset)
{
    setBodyPosition(ScreenUtils::center() + pos + offset);
}
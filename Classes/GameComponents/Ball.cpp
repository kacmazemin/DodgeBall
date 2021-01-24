//
// Created by emin on 24.01.2021.
//

#include "Ball.h"

#include "Box2D/Dynamics/b2World.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "GameLayer.h"


Ball::Ball(b2World &world, const cocos2d::Vec2& startPos, const bool isPlayerBall) : world(&world), startPos(startPos)
{
    this->init();
    autorelease();

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    spriteBody = this->world->CreateBody(&bodyDef);
    spriteBody->SetSleepingAllowed(true);
    spriteBody->SetLinearDamping(1.2);
    spriteBody->SetAngularDamping(0.8);

    //create circle shape
    b2CircleShape circle;
    circle.m_radius =  BALL_RADIUS / PTM_RATIO;

    //define fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = 5;
    fixtureDef.restitution = 0.7;

    if (isPlayerBall)
    {
        //white ball is tracked as bullet by simulation
        spriteBody->SetBullet(true);
        fixtureDef.filter.categoryBits = 0x0100;
    }
    else
    {
        fixtureDef.filter.categoryBits = 0x0010;
    }

    this->initWithFile("ball.png");

    spriteBody->CreateFixture(&fixtureDef);
    spriteBody->SetUserData(this);

    ScreenUtils::fitH(this, BALL_RADIUS * 2.0f);

    createBall();

    if(spriteBody)
    {
        //spriteBody->ApplyLinearImpulse(b2Vec2(100,10), bodyDef.position, false);
    }

}

void Ball::createBall()
{
    setSpritePosition(startPos);
    setColor(cocos2d::Color3B::MAGENTA);
}

void Ball::update(float dt)
{
    if (spriteBody && isVisible()) {
        setPositionX(spriteBody->GetPosition().x * PTM_RATIO);
        setPositionY(spriteBody->GetPosition().y * PTM_RATIO);
    }

}
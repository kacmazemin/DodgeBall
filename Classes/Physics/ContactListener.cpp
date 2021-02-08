//
// Created by emin on 25.01.2021.
//

#include <cocos/base/CCEventCustom.h>
#include "../GameComponents/Ball.h"
#include "../GameComponents/Pocket.h"
#include "ContactListener.h"
#include "Physics/SpriteWithPhysics.h"
#include "SimpleAudioEngine.h"
#include "CCDirector.h"
#include "CCEventDispatcher.h"
#include "AudioManager.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    SpriteWithPhysics* spriteA = static_cast<SpriteWithPhysics*>(bodyA->GetUserData());
    SpriteWithPhysics* spriteB = static_cast<SpriteWithPhysics*>(bodyB->GetUserData());

    if (spriteA && spriteB) {
        if (spriteA->getType() == PhysicsType::BALL &&
            spriteB->getType() == PhysicsType::BALL) {
            if (spriteA->getMagnitude() > 2 && spriteA->isVisible() || spriteB->getMagnitude() > 2 && spriteB->isVisible())
            {
                AudioManager::getInstance()->playBallHitBallEffect();
            }
        }
        else if (spriteA->getType() == PhysicsType::POCKET &&
                 spriteB->getType() == PhysicsType::BALL)
        {
            if(const auto ball = dynamic_cast<Ball*>(spriteB))
            {
                ball->hide();
                cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("onBallHitPocket");
            }

        }
        else if (spriteA->getType() == PhysicsType::POCKET &&
                 spriteB->getType() == PhysicsType::PLAYER_BALL && spriteB->isVisible())
        {
            spriteB->hide();
            AudioManager::getInstance()->playFailEffect();
            cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("onPlayerBallAndPocketCollided");
        }
        else if (spriteA->getType() == PhysicsType::BALL &&
                 spriteB->getType() == PhysicsType::PLAYER_BALL && spriteB->isVisible())
        {
            AudioManager::getInstance()->playBallHitBallEffect();
        }
    }
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)  {

    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    SpriteWithPhysics * spriteA = static_cast<SpriteWithPhysics*>(bodyA->GetUserData());
    SpriteWithPhysics * spriteB = static_cast<SpriteWithPhysics*>(bodyB->GetUserData());

    if (spriteA && spriteB) {

        //track collision between player and cue ball
        if (spriteA->getType() == PhysicsType::CUE && spriteA->getMagnitude() > 2) {
            if (spriteB->getType() == PhysicsType::PLAYER_BALL && spriteB->isVisible())
            {
                AudioManager::getInstance()->playCueHitBall();
                spriteA->hide();
                cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("onCueHitPlayerBall");
            }
        }
    }

}
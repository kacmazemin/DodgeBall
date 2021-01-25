//
// Created by emin on 25.01.2021.
//

#include <cocos/base/CCEventCustom.h>
#include "ContactListener.h"
#include "Physics/SpriteWithPhysics.h"
#include "SimpleAudioEngine.h"

void ContactListener::BeginContact(b2Contact *contact)
{
    b2Body * bodyA = contact->GetFixtureA()->GetBody();
    b2Body * bodyB = contact->GetFixtureB()->GetBody();

    SpriteWithPhysics * spriteA = static_cast<SpriteWithPhysics*>(bodyA->GetUserData());
    SpriteWithPhysics * spriteB = static_cast<SpriteWithPhysics*>(bodyB->GetUserData());

    if (spriteA && spriteB) {
        if (spriteA->getType() == PhysicsType::BALL &&
            spriteB->getType() == PhysicsType::BALL) {
            if (spriteA->getMagnitude() > 5 || spriteB->getMagnitude() > 5)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/cue-hit-ball.wav");
            }

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
            if (spriteB->getType() == PhysicsType::PLAYER_BALL && spriteA->isVisible()) {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/cue-hit-ball.wav");
                spriteA->hide();
            }
        }
//        else if (spriteB->getType() == kSpriteCue && spriteA->mag() > 2)
//        {
//            if (spriteA->getType() == kSpritePlayer && spriteB->isVisible()) {
//                CocosDenshionSimpleAudioEngine::sharedEngine()->playEffect("hit.ogg");
//                spriteB->setVisible(false);
//                spriteA->getGame()->setCanShoot(false);
//            }
//        }

    }

}
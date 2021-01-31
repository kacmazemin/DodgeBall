//
// Created by emin on 23.01.2021.
//

#include "PhysicsManager.h"
#include "ContactListener.h"

#define PTM_RATIO 32

PhysicsManager::PhysicsManager()
{
    world = new b2World(gravity);

    contactListener = new ContactListener();
    world->SetContactListener(contactListener);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    //flags +=b2Draw::e_aabbBit;
    flags += b2Draw::e_centerOfMassBit;
    debugDraw = new GLESDebugDraw(PTM_RATIO);
    debugDraw->AppendFlags(flags);

    world->SetDebugDraw(debugDraw);
}

PhysicsManager::~PhysicsManager()
{
    delete world;
    world = nullptr;

    delete contactListener;
    contactListener = nullptr;

    delete debugDraw;
    debugDraw = nullptr;
}

void PhysicsManager::Update()
{
    //fixed time step for 60fps
    world->Step(1.0f / 60.0f, 10, 10);
}

void PhysicsManager::renderDebug()
{
    world->DrawDebugData();
}

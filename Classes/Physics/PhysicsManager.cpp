//
// Created by emin on 23.01.2021.
//

#include "PhysicsManager.h"

#define SCALE_RATIO 32

PhysicsManager::PhysicsManager()
{
    world = new b2World(gravity);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    //flags +=b2Draw::e_aabbBit;
    flags += b2Draw::e_centerOfMassBit;
    debugDraw = new GLESDebugDraw(SCALE_RATIO);
    debugDraw->AppendFlags(flags);

    world->SetDebugDraw(debugDraw);
}

PhysicsManager::~PhysicsManager()
{
    b2Body* body = world->GetBodyList();

    for (int i = 0; i < world->GetBodyCount(); i++)
    {
        b2Body* existBody = &body[i];
        if (existBody) world->DestroyBody(existBody);
    }

    delete world;
    world = nullptr;

    delete debugDraw;
    debugDraw = nullptr;
}

void PhysicsManager::Update()
{
    int positionIterations = 5;
    int velocityIterations = 1;

    world->Step(1.0 / 60.0, velocityIterations, positionIterations);

}

void PhysicsManager::renderDebug()
{
    world->DrawDebugData();
}

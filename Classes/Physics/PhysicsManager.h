//
// Created by emin on 23.01.2021.
//

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "Utils/GLES-Render.h"
#include "Box2D/Box2D.h"

class ContactListener;

class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    inline b2World* GetWorld()
    {
        return world;
    }

    void Update();
    void renderDebug();

private:
    b2World* world = nullptr;
    b2Vec2 gravity = b2Vec2(0, 0);
    GLESDebugDraw* debugDraw = nullptr;

    ContactListener* contactListener = nullptr;
};


#endif //PHYSICSMANAGER_H

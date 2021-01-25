//
// Created by emin on 25.01.2021.
//

#ifndef _CONTACTLISTENER_H
#define _CONTACTLISTENER_H

#include "Box2D/Box2D.h"

class ContactListener : public b2ContactListener
{
public :
    virtual void BeginContact(b2Contact* contact);
    //virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    //virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};


#endif //_CONTACTLISTENER_H

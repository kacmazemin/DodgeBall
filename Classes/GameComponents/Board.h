//
// Created by emin on 26.01.2021.
//

#ifndef _BOARD_H
#define _BOARD_H

#include <cocos/2d/CCNode.h>
#include "Box2D/Dynamics/b2Body.h"

class b2World;
class b2Body;
class Pocket;

namespace cocos2d
{
   class Sprite;
};

class Board final : public cocos2d::Node
{

public:
    Board(b2World& world);

    void changePhysicsPosition(const cocos2d::Vec2& pos);

private:
    cocos2d::Sprite* tableSprite = nullptr;
    b2World* world = nullptr;
    b2Body* groundBody = nullptr;

    cocos2d::Vec2 pos = cocos2d::Vec2::ZERO;

    std::vector<Pocket*> pockets;

    void createTableSprite();
    void createPhysicEdges();
    void createPockets();

};


#endif //_BOARD_H

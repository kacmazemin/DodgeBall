//
// Created by emin on 26.01.2021.
//

#ifndef _POCKET_H
#define _POCKET_H

#include "../Physics/SpriteWithPhysics.h"

class b2World;

class Pocket final : public SpriteWithPhysics
{
public:
    Pocket(b2World& world, const cocos2d::Vec2& pos);
    ~Pocket();

    void addOffset(const cocos2d::Vec2& offset);

private:
    b2World* world = nullptr;
    cocos2d::Vec2 pos = cocos2d::Vec2::ZERO;

    void createBody();
};


#endif //PROJ_ANDROID_POCKET_H

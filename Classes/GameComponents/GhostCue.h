//
// Created by emin on 24.01.2021.
//

#ifndef _GHOSTCUE_H
#define _GHOSTCUE_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class GhostCue final : public cocos2d::Node
{
public:
    GhostCue();

    cocos2d::Sprite* sprite = nullptr;

    cocos2d::Vec2 getPos() const;

    cocos2d::Vec2 getSpritePosition() const;
private:

    void createSprite();
};


#endif //_GHOSTCUE_H

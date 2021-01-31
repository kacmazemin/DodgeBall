//
// Created by emin on 31.01.2021.
//

#ifndef STARNODE_H
#define STARNODE_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class StarNode final : public cocos2d::Node
{
public:
    StarNode(const cocos2d::Size& size, const cocos2d::Vec2& pos);

private:
    cocos2d::Size size = cocos2d::Size::ZERO;
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;

    cocos2d::Sprite* starSprite = nullptr;

    void createStar();
    void playDisappearAction();
};


#endif //STARNODE_H

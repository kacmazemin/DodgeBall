//
// Created by emin on 28.01.2021.
//

#ifndef LOADINGNODE_H
#define LOADINGNODE_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class LoadingNode final : public cocos2d::Node
{
public:
    LoadingNode(const cocos2d::Size& size);

    virtual void update(float dt) override;

private:
    cocos2d::Sprite* loadingSprite = nullptr;

    void createSprite(const cocos2d::Size& size);
};


#endif //LOADINGNODE_H

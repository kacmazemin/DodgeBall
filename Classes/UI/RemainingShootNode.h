//
// Created by emin on 29.01.2021.
//

#ifndef REMAININGSHOOTNODE_H
#define REMAININGSHOOTNODE_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class RemainingShootNode final : public cocos2d::Node
{
public:
    RemainingShootNode(const float height, const int shootCount);

    void consumeSlot();
    void reset();


private:
    int shootCount = 0;
    int index = 0;
    float height = 0.0f;

    cocos2d::Sprite* background = nullptr;
    std::vector<cocos2d::Sprite*> slots;

    void createBackground();
    void createSlots();
    void playEntranceAnimation();
    void enableTintTo();
    void stopTintTo(const int index);
    void animateTintTo(cocos2d::Node* node);

};


#endif //REMAININGSHOOTNODE_H

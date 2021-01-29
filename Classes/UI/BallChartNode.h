//
// Created by emin on 28.01.2021.
//

#ifndef BALLCHARTNODE_H
#define BALLCHARTNODE_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class BallChartNode final : public cocos2d::Node
{
public:
    BallChartNode(const float height, const int ballCount);

    void setCollected();
    void reset();

private:
    int ballCount = 0;
    float ballInitialScale = 0;
    int index = 0;
    float height = 0;

    cocos2d::Sprite* background = nullptr;

    std::vector<cocos2d::Sprite*> balls;

    void createBackground();
    void createBallSlots();

    void playEntranceAnimation();
    void playBallSortingAnimation();
};


#endif //BALLCHARTNODE_H

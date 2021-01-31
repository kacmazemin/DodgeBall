//
// Created by emin on 28.01.2021.
//

#ifndef CUEPANEL_H
#define CUEPANEL_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
    class ClippingNode;
    class Label;
}
namespace cocos2d::ui
{
    class LoadingBar;
}

class CuePanel final : public cocos2d::Node
{
public:
    CuePanel(const cocos2d::Size& size);

    void changeActivity(const bool isActive);

    float getPowerFromBar() const;

    virtual void update(float dt) override;

private:
    float percent = 0;
    bool isHitMax = false;
    cocos2d::Size size = cocos2d::Size::ZERO;

    cocos2d::Sprite* background = nullptr;
    cocos2d::ui::LoadingBar* bar = nullptr;

    void createBackground();
    void createBar();
};


#endif //CUEPANEL_H

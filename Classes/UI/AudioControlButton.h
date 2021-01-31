//
// Created by emin on 30.01.2021.
//

#ifndef AUDIOCONTROLBUTTON_H
#define AUDIOCONTROLBUTTON_H

#include <cocos/2d/CCNode.h>
#include <extensions/GUI/CCControlExtension/CCControl.h>

namespace cocos2d
{
    class Sprite;
}
namespace cocos2d::extension
{
    class ControlSwitch;
}

class AudioControlButton final : public cocos2d::Node
{
public:
    AudioControlButton(const cocos2d::Size& size);

private:
    cocos2d::Size size = cocos2d::Size::ZERO;

    cocos2d::extension::ControlSwitch* switchButton = nullptr;

    void createButton();
    void valueChanged(cocos2d::Ref * sender, cocos2d::extension::Control::EventType);
};


#endif //AUDIOCONTROLBUTTON_H

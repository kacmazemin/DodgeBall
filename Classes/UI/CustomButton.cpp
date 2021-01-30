//
// Created by emin on 29.01.2021.
//

#include "CustomButton.h"
#include "../Utils/ScreenUtils.h"
#include <cocos/ui/UIButton.h>
#include "../AudioManager.h"

CustomButton::CustomButton(const std::string& path, const cocos2d::Size& size)
: imagePath(path), size(size)
{
    cocos2d::Node::init();
    autorelease();

    createButton();
}

void CustomButton::createButton()
{
    //this node created to get bounding box of button.
    initialNode = cocos2d::Node::create();

    addChild(initialNode);

    mainButton = cocos2d::ui::Button::create(imagePath);
    mainButton->setZoomScale(-mainButton->getZoomScale());
    ScreenUtils::fitH(mainButton, size.height);

    mainButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                playClickEffect();
                break;
            case cocos2d::ui::Widget::TouchEventType::MOVED:
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED:

                if(function)
                {
                    function();
                }
                break;
            default:
                break;
        }
    });

    initialNode->addChild(mainButton);
}

void CustomButton::setOnTap(const std::function<void()>& func)
{
    function = func;
}


cocos2d::Rect CustomButton::getBoundingBox() const
{
    return cocos2d::utils::getCascadeBoundingBox(initialNode);
}

void CustomButton::playClickEffect()
{
    if(isSoundEffectEnable)
    {
        AudioManager::getInstance()->playButtonClick();
    }
}

void CustomButton::changeSoundActivity(const bool isEnable)
{
    isSoundEffectEnable = isEnable;
}

void CustomButton::enableTintTo()
{
    cocos2d::Action* tintToAction = cocos2d::RepeatForever::create(cocos2d::Sequence::create({
             cocos2d::TintTo::create(.6f, cocos2d::Color3B::WHITE),
             cocos2d::TintTo::create(.2f, cocos2d::Color3B::GRAY)
     }));

    mainButton->runAction(tintToAction);
}

void CustomButton::addLabel(const std::string& string, const float heightRatio)
{
    if(mainButton)
    {
        auto* label = cocos2d::Label::createWithTTF(string,
                "fonts/bowly.ttf",  mainButton->getBoundingBox().size.height * heightRatio);
        label->setTextColor(cocos2d::Color4B::WHITE);
        label->enableOutline(cocos2d::Color4B::BLACK, 2);

        mainButton->setTitleLabel(label);
    }
}

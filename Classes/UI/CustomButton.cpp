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
    initialNode = cocos2d::Node::create();
    initialNode->setScale(1.f);
    initialScale = initialNode->getScale();

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

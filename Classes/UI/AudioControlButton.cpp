//
// Created by emin on 30.01.2021.
//

#include "AudioControlButton.h"
#include "AudioManager.h"
#include <cocos/2d/CCSprite.h>
#include <cocos/deprecated/CCDeprecated.h>
#include "../Utils/ScreenUtils.h"
#include "extensions/GUI/CCControlExtension/CCControlSwitch.h"
#include "extensions/GUI/CCControlExtension/CCInvocation.h"

namespace
{
    const std::string maskPath = "textures/main-menu/control-button-bg.png";
    const std::string thumbPath = "textures/main-menu/control-thumb.png";
    const std::string controlOnPath = "textures/main-menu/control-button-on.png";
    const std::string controlOffPath = "textures/main-menu/control-button-off.png";
}

AudioControlButton::AudioControlButton(const cocos2d::Size& size) : size(size)
{
    cocos2d::Node::init();
    autorelease();

    createButton();
}


void AudioControlButton::createButton()
{
    cocos2d::Sprite* mask = cocos2d::Sprite::create(maskPath);
    cocos2d::Sprite* controlOn = cocos2d::Sprite::create(controlOnPath);
    cocos2d::Sprite* controlOff = cocos2d::Sprite::create(controlOffPath);
    cocos2d::Sprite* controlThumb = cocos2d::Sprite::create(thumbPath);

    switchButton = cocos2d::extension::ControlSwitch::create(mask,controlOn,controlOff,controlThumb);

    ScreenUtils::fitH(switchButton, size.height * .1f);
    switchButton->setOn(!AudioManager::getInstance()->getIsMuted());

    switchButton->addTargetWithActionForControlEvents(this,
            cccontrol_selector(AudioControlButton::valueChanged), cocos2d::extension::Control::EventType::VALUE_CHANGED);

    addChild(switchButton);
}

void AudioControlButton::valueChanged(cocos2d::Ref * sender, cocos2d::extension::Control::EventType)
{
    if(switchButton)
    {
        AudioManager::getInstance()->mute(!switchButton->isOn());
    }
}


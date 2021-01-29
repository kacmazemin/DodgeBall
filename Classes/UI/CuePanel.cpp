//
// Created by emin on 28.01.2021.
//

#include "CuePanel.h"
#include <cocos/2d/CCSprite.h>
#include <cocos/ui/UILoadingBar.h>
#include "../Utils/ScreenUtils.h"

CuePanel::CuePanel(const cocos2d::Size& size) : size(size)
{
    cocos2d::Node::init();
    autorelease();

    createBackground();
    createBar();

    scheduleUpdate();
}

void CuePanel::createBackground()
{
    background = cocos2d::Sprite::create("textures/cue-panel-bar-bg.png");
    ScreenUtils::fitW(background, size.width);

    addChild(background);

}

void CuePanel::createBar()
{
    bar = cocos2d::ui::LoadingBar::create("textures/bar-gradient-fill-texture.png");
    ScreenUtils::fitW(bar, background->getBoundingBox().size.height);
    background->setRotation(90);

    addChild(bar);
}

void CuePanel::update(float dt)
{
    if(bar->getPercent() >= 100.0f)
    {
        isHitMax = true;
    }
    else if(bar->getPercent() <= 0.f)
    {
        isHitMax = false;
    }

    percent = isHitMax ? percent - (dt * 150) :  percent + (dt * 150);

    if(bar)
    {
        bar->setPercent(percent);
    }
}

void CuePanel::changeActivity(const bool isActive)
{
    if(!isActive)
    {
        this->unscheduleUpdate();
    }
    else
    {
        this->scheduleUpdate();
    }
}

float CuePanel::getPowerFromBar() const
{
    return std::max(15.f, percent);
}
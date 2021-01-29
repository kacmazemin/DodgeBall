//
// Created by emin on 29.01.2021.
//

#include "RemainingShootNode.h"
#include "../Utils/ScreenUtils.h"

namespace
{
    const std::string bgPath = "textures/chart/remaining-panel-bg.png";
    const std::string activeSocketSpritePath = "textures/chart/player-ball-slot.png";
    const std::string inActiveSocketSpritePath = "textures/chart/passive-ball-slot.png";
    constexpr int tintToActionNo = 444;
}

RemainingShootNode::RemainingShootNode(const float height, const int shootCount)
: height(height), shootCount(shootCount)
{
    cocos2d::Node::init();
    autorelease();

    createBackground();
    createSlots();

    playEntranceAnimation();

}

void RemainingShootNode::createBackground()
{
    background = cocos2d::Sprite::create(bgPath);
    ScreenUtils::fitH(background, height);
    addChild(background);

    background->setPositionY(-background->getBoundingBox().size.height * .5f);
}

void RemainingShootNode::createSlots()
{
    const float width = background->getBoundingBox().size.width;
    const float offset = width * .05f;
    const float startX = background->getBoundingBox().getMinX() + offset;
    const float yPos = background->getBoundingBox().getMidY();
    const float space = height * .1f;
    const float ballWidth = (width - (offset * 2) - ((shootCount - 1) * space)) / shootCount;

    for (int i = 0; i < shootCount ; i++)
    {
        auto* ballSprite = cocos2d::Sprite::create(activeSocketSpritePath);
        ScreenUtils::fitW(ballSprite, ballWidth);
        ballSprite->setPositionY(yPos);
        ballSprite->setPositionX(startX + (ballWidth * .5f) + (i * (space + ballWidth)));
        addChild(ballSprite, 1);

        slots.emplace_back(ballSprite);
    }

    index = slots.size() - 1;
}

void RemainingShootNode::playEntranceAnimation()
{
    runAction(cocos2d::Sequence::create({
        cocos2d::DelayTime::create(.5f),
        cocos2d::EaseSineIn::create(cocos2d::MoveBy::create(.5f, {0, height})),
        cocos2d::CallFunc::create([=](){
            enableTintTo();
        })
    }));
}

void RemainingShootNode::consumeSlot()
{
    if(index < slots.size() && index >= 0)
    {
        slots[index]->setTexture(inActiveSocketSpritePath);
        stopTintTo(index);
        index--;
    }
}

void RemainingShootNode::reset()
{
    for (const auto& singleSlot : slots)
    {
        singleSlot->setTexture(activeSocketSpritePath);
    }

    enableTintTo();
    index = slots.size() - 1;
}

void RemainingShootNode::enableTintTo()
{
    for (const auto& singleSlot : slots)
    {
        animateTintTo(singleSlot);
    }
}

void RemainingShootNode::stopTintTo(const int index)
{
    if(auto node = slots[index])
    {
        if(node->getNumberOfRunningActionsByTag(tintToActionNo) > 0)
        {
            node->stopAllActionsByTag(tintToActionNo);
        }
    }
}

void RemainingShootNode::animateTintTo(cocos2d::Node* node)
{
    cocos2d::Action* tintToAction = cocos2d::RepeatForever::create(cocos2d::Sequence::create({
         cocos2d::TintTo::create(.6f, cocos2d::Color3B::GRAY),
         cocos2d::TintTo::create(.4f, cocos2d::Color3B::WHITE)
     }));

    tintToAction->setTag(tintToActionNo);

    if(node && node->getNumberOfRunningActionsByTag(tintToActionNo) == 0)
    {
        node->runAction(tintToAction);
    }
}


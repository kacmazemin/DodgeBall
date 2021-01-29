//
// Created by emin on 29.01.2021.
//

#include "AnnouncerNode.h"
#include <cocos/2d/CCLabel.h>
#include "../Utils/ScreenUtils.h"

namespace
{
    const std::string fontPath = "fonts/bowly.ttf";
    constexpr int actionTag = 777;
}

AnnouncerNode::AnnouncerNode()
{
    cocos2d::Node::init();
    autorelease();

    createMainLabel();
}

void AnnouncerNode::createMainLabel()
{
    screenSize = ScreenUtils::getVisibleRect().size;

    mainLabel = cocos2d::Label::createWithTTF("Deneme", fontPath, screenSize.height * .2f);
    mainLabel->enableGlow(cocos2d::Color4B::GREEN);
    mainLabel->setTextColor(cocos2d::Color4B::BLACK);
    mainLabel->setVisible(false);
    mainLabel->enableOutline(cocos2d::Color4B::MAGENTA, 1);

    addChild(mainLabel);
}

void AnnouncerNode::makeAnnounce(const AnnounceType type)
{
    if(mainLabel->getNumberOfRunningActionsByTag(actionTag) == 0)
    {
        announceType = type;
        mainLabel->setVisible(true);
        handleStringContent();

        const float labelWidth = mainLabel->getBoundingBox().size.width;
        const float startX = ScreenUtils::left().x - labelWidth;

        mainLabel->setPositionX(startX);

        cocos2d::Action* action = cocos2d::Sequence::create({
            cocos2d::EaseSineInOut::create(cocos2d::MoveTo::create(.4f, cocos2d::Vec2{0 , 0})),
            cocos2d::DelayTime::create(.5f),
            cocos2d::EaseSineInOut::create(cocos2d::MoveTo::create(.6f,
                    {ScreenUtils::right().x + labelWidth, 0})),
            cocos2d::CallFunc::create([=](){
                mainLabel->setVisible(false);
            })
        });
        action->setTag(actionTag);

        mainLabel->runAction(action);
    }
}

void AnnouncerNode::handleStringContent()
{
    switch (announceType)
    {
        case AnnounceType::GameStart:
            stringContent = "Good Luck";
            break;
        case AnnounceType::Score:
            stringContent = "Score!";
            break;
        case AnnounceType::Fail:
            stringContent = "Fail";
            break;
        case AnnounceType::Win:
            stringContent = "Congratulations";
            break;
        case AnnounceType::EndGame:
            stringContent = "You Lost!";
            break;
        case AnnounceType::Undefined:
            stringContent = "Undefined";
            break;
    }

    mainLabel->setString(stringContent);
}

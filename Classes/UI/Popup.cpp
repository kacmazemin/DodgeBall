//
// Created by emin on 30.01.2021.
//

#include "Popup.h"
#include <cocos/2d/CCSprite.h>
#include "Utils/ScreenUtils.h"
#include "CustomButton.h"

Popup::Popup()
{
    cocos2d::Node::init();
    autorelease();

    createBackground();
    createTouchListener();

    createCloseButton();
}

void Popup::createBackground()
{
    contentNode = cocos2d::Node::create();
    addChild(contentNode);

    backgroundSprite = cocos2d::Sprite::create("textures/popup-layout.png");
    ScreenUtils::fitWH(backgroundSprite, ScreenUtils::getVisibleRect().size.width,
                                         ScreenUtils::getVisibleRect().size.height);

    contentNode->addChild(backgroundSprite);
}

void Popup::createTouchListener()
{
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
    {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Popup::createCloseButton()
{
    auto* closeButton = new CustomButton("textures/close-button.png", backgroundSprite->getBoundingBox().size * .1f);

    closeButton->setPositionX(backgroundSprite->getBoundingBox().getMaxX() - closeButton->getBoundingBox().size.width * .75f);
    closeButton->setPositionY(backgroundSprite->getBoundingBox().getMaxY() - closeButton->getBoundingBox().size.height * .75f);

    closeButton->setOnTap([=]()
    {
        this->removeFromParentAndCleanup(true);
    });

    contentNode->addChild(closeButton);
}

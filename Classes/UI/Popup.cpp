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

    createLayout();
    createTouchListener();

    createCloseButton();
}

void Popup::createLayout()
{
    contentNode = cocos2d::Node::create();
    addChild(contentNode);

    layoutSprite = cocos2d::Sprite::create("textures/popup-layout.png");
    ScreenUtils::fitWH(layoutSprite, ScreenUtils::getVisibleRect().size.width,
                                         ScreenUtils::getVisibleRect().size.height);

    contentNode->addChild(layoutSprite);
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
    closeButton = new CustomButton("textures/close-button.png", layoutSprite->getBoundingBox().size * .1f);

    closeButton->setPositionX(layoutSprite->getBoundingBox().getMaxX() - closeButton->getBoundingBox().size.width * .75f);
    closeButton->setPositionY(layoutSprite->getBoundingBox().getMaxY() - closeButton->getBoundingBox().size.height * .75f);

    closeButton->setOnTap([=]()
    {
        closePopup();
    });

    contentNode->addChild(closeButton, 2);
}

void Popup::fitCloseButton(const cocos2d::Rect& rect)
{
    if(closeButton)
    {
        closeButton->setPositionX(rect.getMaxX() - closeButton->getBoundingBox().size.width * .9f);
        closeButton->setPositionY(rect.getMaxY() - closeButton->getBoundingBox().size.height * .9f);
    }

}

void Popup::closePopup()
{
    this->removeFromParentAndCleanup(true);
}

void Popup::changeCloseButtonVisibility(const bool isVisible)
{
    closeButton->setVisible(isVisible);
}

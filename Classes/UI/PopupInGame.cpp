//
// Created by emin on 30.01.2021.
//

#include "PopupInGame.h"
#include <cocos/2d/CCSprite.h>
#include "../Utils/ScreenUtils.h"
#include "CustomButton.h"

namespace
{
    const std::string fontPath = "fonts/bowly.ttf";
}

PopupInGame::PopupInGame(const bool isMatchEnd): isMatchEnd(isMatchEnd)
{
    createBackground();
    createHeader();
    createSubTitle();
    createBottomButtons();

    changeCloseButtonVisibility(false);
}

void PopupInGame::createBackground()
{
    background = cocos2d::Sprite::create("textures/popup-background.png");
    ScreenUtils::fitH(background, ScreenUtils::getVisibleRect().size.height * .6f);

    contentNode->addChild(background);

    fitCloseButton(background->getBoundingBox());
}

void PopupInGame::createHeader()
{
    const auto backgroundBB = background->getBoundingBox();

    std::string textContent = isMatchEnd ? "Game Over" : "Warning";

    headerLabel = cocos2d::Label::createWithTTF(textContent, fontPath, backgroundBB.size.height * .2f);
    headerLabel->setTextColor(cocos2d::Color4B::WHITE);
    headerLabel->enableOutline(cocos2d::Color4B::BLACK, 2);

    headerLabel->setPositionY(backgroundBB.getMaxY() - headerLabel->getBoundingBox().size.height * .5f);

    contentNode->addChild(headerLabel);
}

void PopupInGame::createSubTitle()
{
    const auto backgroundBB = background->getBoundingBox();

    std::string textContent = isMatchEnd ? "Would you like to play one more time?" : "Return To Main Menu";

    subTitle = cocos2d::Label::createWithTTF(textContent, fontPath, backgroundBB.size.height * .08f);
    subTitle->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
    subTitle->setTextColor(cocos2d::Color4B::WHITE);
    subTitle->enableOutline(cocos2d::Color4B::BLACK, 2);

    subTitle->setPositionY(headerLabel->getBoundingBox().getMinY() - headerLabel->getBoundingBox().size.height * .1f);

    contentNode->addChild(subTitle);
}

void PopupInGame::createBottomButtons()
{
    const auto backgroundBB = background->getBoundingBox();

    yesButton = new CustomButton("textures/purple-button.png", backgroundBB.size * .2f);
    yesButton->addLabel("YES", .6f);

    yesButton->setPositionX(backgroundBB.getMinX() + yesButton->getBoundingBox().size.width * 1.2f);
    yesButton->setPositionY(backgroundBB.getMinY() +  yesButton->getBoundingBox().size.height * 1.2f);

    yesButton->setOnTap([=]()
    {
        if(yesFunction)
        {
            yesFunction();
        }
        closePopup();
    });

    contentNode->addChild(yesButton);

    noButton = new CustomButton("textures/purple-button.png", backgroundBB.size * .2f);
    noButton->addLabel("NO", .6f);

    noButton->setPositionX(backgroundBB.getMaxX() - noButton->getBoundingBox().size.width * 1.2f );
    noButton->setPositionY(backgroundBB.getMinY() + noButton->getBoundingBox().size.height * 1.2f);

    noButton->setOnTap([=]()
    {
        if(noFunction)
        {
            noFunction();
        }
        closePopup();
    });

    contentNode->addChild(noButton);
}

void PopupInGame::setYesOnTapFunction(const std::function<void()>& func)
{
    yesFunction = func;
}

void PopupInGame::setNoOnTapFunction(const std::function<void()>& func)
{
    noFunction = func;
}
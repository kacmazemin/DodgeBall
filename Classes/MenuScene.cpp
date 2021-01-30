//
// Created by emin on 23.01.2021.
//

#include "MenuScene.h"
#include "UI/CustomButton.h"
#include "Utils/ScreenUtils.h"
#include "GameLayer.h"

cocos2d::Scene *MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    auto* yesButton = new CustomButton("textures/purple-button.png", ScreenUtils::getVisibleRect().size * .2f);
    yesButton->addLabel("THIS IS A SUCCESS STORY", .6f);

    yesButton->setPosition(ScreenUtils::center());

    yesButton->setOnTap([=]()
    {
        auto scene = GameLayer::createScene();
        // run
        cocos2d::Director::getInstance()->runWithScene(scene);
    });

    addChild(yesButton);

    return true;
}

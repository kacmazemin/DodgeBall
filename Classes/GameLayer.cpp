//
// Created by emin on 23.01.2021.
//

#include "GameLayer.h"
#include "ScreenUtils.h"

cocos2d::Scene *GameLayer::createScene()
{
    return GameLayer::create();
}

bool GameLayer::init()
{
    // 1. super init first
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    auto label = cocos2d::Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 1);

    cocos2d::Sprite* sprite = cocos2d::Sprite::create("HelloWorld.png");
    sprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

    sprite->setPosition(ScreenUtils::leftTop());

    this->addChild(sprite, 0);

    return true;
}

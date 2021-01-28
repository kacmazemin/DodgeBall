//
// Created by emin on 28.01.2021.
//

#include "LoadingNode.h"
#include <cocos/2d/CCSprite.h>
#include "../Utils/ScreenUtils.h"

LoadingNode::LoadingNode(const cocos2d::Size& size)
{
    cocos2d::Node::init();
    autorelease();

    createSprite(size);

    scheduleUpdate();
}

void LoadingNode::createSprite(const cocos2d::Size& size)
{
    loadingSprite = cocos2d::Sprite::create("textures/loading-sprite.png");
    loadingSprite->setColor(cocos2d::Color3B::ORANGE);
    ScreenUtils::fitH(loadingSprite, size.height);
    addChild(loadingSprite);
}

void LoadingNode::update(float dt)
{
    if(loadingSprite && isVisible())
    {
        loadingSprite->setRotation(loadingSprite->getRotation() + (dt * 180));
    }
}

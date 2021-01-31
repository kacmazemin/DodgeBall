//
// Created by emin on 24.01.2021.
//

#include "GhostCue.h"
#include "../Utils/ScreenUtils.h"
#include "Ball.h"

GhostCue::GhostCue()
{
    cocos2d::Node::init();
    autorelease();

    createSprite();
}

void GhostCue::createSprite()
{
    sprite = cocos2d::Sprite::create("textures/cue.png");

    ScreenUtils::fitW(sprite, BALL_RADIUS * 22);

    sprite->setPositionX( sprite->getBoundingBox().size.width * .5f + (BALL_RADIUS * 3));

    addChild(sprite);
}

cocos2d::Vec2 GhostCue::getPos() const
{
    return convertToWorldSpace(sprite->getPosition());
}

cocos2d::Vec2 GhostCue::getSpritePosition() const
{
    return convertToWorldSpace(sprite->getPosition());
}

//
// Created by emin on 31.01.2021.
//

#include "StarNode.h"
#include <cocos/2d/CCSprite.h>
#include "Utils/ScreenUtils.h"

StarNode::StarNode(const cocos2d::Size &size, const cocos2d::Vec2 &pos): size(size), position(pos)
{
    cocos2d::Node::init();
    autorelease();

    createStar();
    playDisappearAction();
}

void StarNode::createStar()
{
    starSprite = cocos2d::Sprite::create("textures/star.png");
    ScreenUtils::fitH(starSprite, size.height);

    addChild(starSprite);

}

void StarNode::playDisappearAction()
{
    starSprite->runAction(cocos2d::Sequence::create({
        cocos2d::EaseSineInOut::create(cocos2d::ScaleTo::create(1.f,0.f)),
        cocos2d::DelayTime::create(.2f),
        cocos2d::CallFunc::create([=](){
                this->removeFromParentAndCleanup(true);
            })
        }));
}


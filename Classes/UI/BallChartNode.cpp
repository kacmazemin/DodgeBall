//
// Created by emin on 28.01.2021.
//

#include "BallChartNode.h"
#include <cocos/2d/CCSprite.h>
#include "../Utils/ScreenUtils.h"

namespace
{
    const std::string chartBgPath = "textures/chart/ball-chart-bg.png";
    const std::string activeSocketSpritePath = "textures/chart/active-ball-slot.png";
    const std::string inActiveSocketSpritePath = "textures/chart/passive-ball-slot.png";
}

BallChartNode::BallChartNode(const float height, const int ballCount)
: height(height), ballCount(ballCount)
{
    cocos2d::Node::init();
    autorelease();

    createBackground();
    createBallSlots();

    playEntranceAnimation();
}

void BallChartNode::createBackground()
{
    background = cocos2d::Sprite::create(chartBgPath);
    ScreenUtils::fitH(background, height);
    addChild(background);

    background->setPositionY(background->getBoundingBox().size.height * .5f);

}

void BallChartNode::createBallSlots()
{
    const float width = background->getBoundingBox().size.width;
    const float offset = width * .05f;
    const float startX = background->getBoundingBox().getMinX() + offset;
    const float yPos = background->getBoundingBox().getMidY();
    const float space = height * .1f;
    const float ballWidth = (width - (offset * 2) - ((ballCount - 1) * space)) / ballCount;


    for (int i = 0; i < ballCount ; i++)
    {
        auto* ballSprite = cocos2d::Sprite::create(inActiveSocketSpritePath);
        ScreenUtils::fitW(ballSprite, ballWidth);
        ballSprite->setPositionY(yPos);
        ballSprite->setPositionX(startX + (ballWidth * .5f) + (i * (space + ballWidth)));
        addChild(ballSprite, 1);

        if(i == 0)
        {
            ballInitialScale = ballSprite->getScale();
        }

        //since no need to make operation like delete element etc. emplace back is more optimized.
        balls.emplace_back(ballSprite);

        ballSprite->setScale(0);
    }
}

void BallChartNode::playEntranceAnimation()
{
    runAction(cocos2d::Sequence::create({
        cocos2d::DelayTime::create(.5f),
        cocos2d::EaseSineIn::create(cocos2d::MoveBy::create(.5f, {0, -height})),
        cocos2d::DelayTime::create(.5f),
        cocos2d::CallFunc::create([=]()
        {
            playBallSortingAnimation();
        })
    }));
}

void BallChartNode::playBallSortingAnimation()
{
    for (int i = 0; i < balls.size(); i++)
    {
        balls[i]->runAction(cocos2d::Sequence::create(
        {
            cocos2d::DelayTime::create(.1f * i),
            cocos2d::EaseExponentialIn::create(cocos2d::ScaleTo::create(.2f, ballInitialScale))
        }));
    }
}

void BallChartNode::setCollected()
{
    balls[index]->setTexture(activeSocketSpritePath);
    index++;
}
void BallChartNode::reset()
{
    index = 0;

    for (const auto& socket : balls)
    {
        socket->setTexture(inActiveSocketSpritePath);
    }
}
//
// Created by emin on 23.01.2021.
//

#include "ScreenUtils.h"

USING_NS_CC;

Rect ScreenUtils::s_visibleRect;

void ScreenUtils::lazyInit()
{
    // no lazy init
    // Useful if we change the resolution in runtime
    s_visibleRect = Director::getInstance()->getOpenGLView()->getVisibleRect();
}

Rect ScreenUtils::getVisibleRect()
{
    lazyInit();
    return s_visibleRect;
}

Vec2 ScreenUtils::left()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 ScreenUtils::right()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 ScreenUtils::top()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 ScreenUtils::bottom()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

Vec2 ScreenUtils::center()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

Vec2 ScreenUtils::leftTop()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 ScreenUtils::rightTop()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

Vec2 ScreenUtils::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

Vec2 ScreenUtils::rightBottom()
{
    lazyInit();
    return Vec2(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}

void ScreenUtils::fitH(cocos2d::Node* node, float height)
{
    node->setScale(height / node->getContentSize().height);
}

void ScreenUtils::fitW(cocos2d::Node *node, float width)
{
    node->setScale(width / node->getContentSize().width);
}

void ScreenUtils::fitWH(cocos2d::Node *node, float width, float height)
{
    node->setScaleX(width / node->getContentSize().width);
    node->setScaleY(height / node->getContentSize().height);
}
//
// Created by emin on 23.01.2021.
//

#ifndef _SCREENUTILS_H
#define _SCREENUTILS_H

#include "cocos2d.h"

#define PTM_RATIO 32

class ScreenUtils {

public:
    static cocos2d::Rect getVisibleRect();

    static cocos2d::Vec2 left();
    static cocos2d::Vec2 right();
    static cocos2d::Vec2 top();
    static cocos2d::Vec2 bottom();
    static cocos2d::Vec2 center();
    static cocos2d::Vec2 leftTop();
    static cocos2d::Vec2 rightTop();
    static cocos2d::Vec2 leftBottom();
    static cocos2d::Vec2 rightBottom();

    static void fitH(cocos2d::Node* node , float height);
    static void fitW(cocos2d::Node* node , float width);
    static void fitWH(cocos2d::Node* node , float width, float height);

private:
    static void lazyInit();
    static cocos2d::Rect s_visibleRect;
};


#endif //_SCREENUTILS_H

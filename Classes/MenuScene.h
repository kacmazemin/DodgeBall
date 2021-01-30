//
// Created by emin on 23.01.2021.
//

#ifndef _MENUSCENE_H
#define _MENUSCENE_H

#include <cocos/2d/CCScene.h>

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MenuScene);

};


#endif _MENUSCENE_H

//
// Created by emin on 30.01.2021.
//

#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <cocos/2d/CCScene.h>

class SplashScreen final : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(SplashScreen);

private:
    void createLogo();
};


#endif //SPLASHSCREEN_H

//
// Created by emin on 30.01.2021.
//

#include "SplashScreen.h"
#include "MenuScene.h"
#include <cocos/2d/CCSprite.h>
#include "Utils/ScreenUtils.h"
#include "UI/CustomButton.h"
#include "AudioManager.h"

namespace
{
    const std::string logoPath = "textures/splash/logo.png";
}

cocos2d::Scene *SplashScreen::createScene()
{
    return SplashScreen::create();
}

bool SplashScreen::init()
{
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    createLogo();


    return true;
}

void SplashScreen::createLogo()
{
    auto* logo = cocos2d::Sprite::create(logoPath);
    ScreenUtils::fitH(logo,ScreenUtils::getVisibleRect().size.height * .35f);
    logo->setPositionY(ScreenUtils::bottom().y - logo->getBoundingBox().size.height * .5f);
    logo->setPositionX(ScreenUtils::bottom().x);

    addChild(logo);

    logo->runAction(cocos2d::Sequence::create({
          cocos2d::DelayTime::create(1.f),
          cocos2d::EaseElasticOut::create(cocos2d::MoveTo::create(2.f,ScreenUtils::center()), .2f),
          cocos2d::DelayTime::create(2.f),
          cocos2d::CallFunc::create([=]()
          {
            auto* scene = MenuScene::create();
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionShrinkGrow::create(.5f, scene));
          })
     }));

    logo->runAction(cocos2d::Sequence::create({
        cocos2d::DelayTime::create(1.f),
        cocos2d::CallFunc::create([=](){
            AudioManager::getInstance()->playSoundEffect("Sounds/splash.wav", 1.f);
        })
    }));

}




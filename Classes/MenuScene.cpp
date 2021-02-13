//
// Created by emin on 23.01.2021.
//

#include "MenuScene.h"
#include "UI/CustomButton.h"
#include "Utils/ScreenUtils.h"
#include "GameLayer.h"
#include "UI/AudioControlButton.h"
#include "AudioManager.h"

namespace
{
    const std::string backgroundPath = "textures/main-menu/main-menu-bg.png";
    const std::string layoutPath = "textures/main-menu/menu-layout.png";
    const std::string layoutLinePath = "textures/main-menu/menu-layout-line.png";
    const std::string playButtonPath = "textures/main-menu/play-button.png";
    const std::string exitButtonPath = "textures/main-menu/exit-button.png";
}

cocos2d::Scene *MenuScene::createScene()
{
    return MenuScene::create();
}

bool MenuScene::init()
{
    if ( !cocos2d::Scene::init() )
    {
        return false;
    }

    initialNode = cocos2d::Node::create();
    initialNode->setPosition(ScreenUtils::center());
    addChild(initialNode);

    createBackground();
    createLayout();
    createLayoutLines();
    createPlayButton();
    createExitButton();
    createAudioControlButton();

    playLayoutLineAction();

    AudioManager::getInstance()->playMenuMusic();

    return true;
}

void MenuScene::createBackground()
{
    background = cocos2d::Sprite::create(backgroundPath);
    ScreenUtils::fitWH(background, ScreenUtils::getVisibleRect().size.width ,ScreenUtils::getVisibleRect().size.height);
    background->setBlendFunc(cocos2d::BlendFunc{GL_SRC_ALPHA, GL_ONE});
//    ScreenUtils::fitH(background, ScreenUtils::getVisibleRect().size.height);
    initialNode->addChild(background);
}


void MenuScene::createLayout()
{
    layout = cocos2d::Sprite::create(layoutPath);
    ScreenUtils::fitH(layout, background->getBoundingBox().size.height);
    initialNode->addChild(layout);
}

void MenuScene::createLayoutLines()
{
    layoutLines = cocos2d::Sprite::create(layoutLinePath);
    ScreenUtils::fitH(layoutLines, layout->getBoundingBox().size.height);
    layoutLines->setOpacity(0);

    initialNode->addChild(layoutLines);
}


void MenuScene::createPlayButton()
{
    playButton = new CustomButton(playButtonPath, layout->getBoundingBox().size * .5f);
    playButton->setPositionX(layout->getBoundingBox().getMinX() + playButton->getBoundingBox().size.width);

    playButton->setOnTap([=]()
     {
         auto scene = GameLayer::createScene();
         cocos2d::Director::getInstance()->runWithScene(scene);
     });

    playButton->enableLightShader();

    initialNode->addChild(playButton);
}

void MenuScene::createExitButton()
{

    exitButton = new CustomButton(exitButtonPath, layout->getBoundingBox().size * .5f);
    exitButton->setPositionX(layout->getBoundingBox().getMaxX() - exitButton->getBoundingBox().size.width);

    exitButton->setOnTap([=]()
     {
         cocos2d::Director::getInstance()->end();
     });

    exitButton->enableLightShader();

    initialNode->addChild(exitButton);
}


void MenuScene::playLayoutLineAction()
{
    auto lightedAction = cocos2d::Sequence::create({
       cocos2d::CallFunc::create([=](){
           layoutLines->setOpacity(100);
       }),
       cocos2d::DelayTime::create(.06f),
       cocos2d::CallFunc::create([=](){
           layoutLines->setOpacity(0);
       }),
       cocos2d::DelayTime::create(.1f),
       cocos2d::CallFunc::create([=](){
           layoutLines->setOpacity(100);
       }),
       cocos2d::DelayTime::create(.06f),
       cocos2d::CallFunc::create([=](){
           layoutLines->setOpacity(0);
       }),
       cocos2d::DelayTime::create(.2f),
       });

    runAction(cocos2d::Sequence::create({
           cocos2d::DelayTime::create(1.2f),
           cocos2d::Repeat::create(lightedAction, 5),
           cocos2d::CallFunc::create([=](){
               layoutLines->setOpacity(150);
           }),
           cocos2d::DelayTime::create(.5f),
           cocos2d::CallFunc::create([=](){
               layoutLines->setOpacity(255);
           }),
       }));
}

void MenuScene::createAudioControlButton()
{
    audioControlButton = new AudioControlButton(ScreenUtils::getVisibleRect().size);
    initialNode->addChild(audioControlButton, 10);
}
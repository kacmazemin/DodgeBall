//
// Created by emin on 23.01.2021.
//

#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <cocos/2d/CCScene.h>

namespace cocos2d
{
    class Sprite;
}

class CustomButton;
class AudioControlButton;

class MenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MenuScene);

private:
    cocos2d::Node* initialNode = nullptr;

    cocos2d::Sprite* background = nullptr;
    cocos2d::Sprite* layout = nullptr;
    cocos2d::Sprite* layoutLines = nullptr;

    CustomButton* playButton = nullptr;
    CustomButton* exitButton = nullptr;

    AudioControlButton* audioControlButton = nullptr;

    void createBackground();
    void createLayout();
    void createLayoutLines();

    void createPlayButton();
    void createExitButton();

    void createAudioControlButton();

    void playLayoutLineAction();

};


#endif //MENUSCENE_H

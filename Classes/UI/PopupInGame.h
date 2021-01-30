//
// Created by emin on 30.01.2021.
//

#ifndef POPUPINGAME_H
#define POPUPINGAME_H

#include "Popup.h"

namespace cocos2d
{
    class Label;
}

class CustomButton;

class PopupInGame : public Popup
{
public:
    PopupInGame(const bool isMatchEnd);

    void setYesOnTapFunction(const std::function<void()>& func);
    void setNoOnTapFunction(const std::function<void()>& func);

private:
    bool isMatchEnd = false;
    cocos2d::Sprite* background = nullptr;

    cocos2d::Label* headerLabel = nullptr;
    cocos2d::Label* subTitle = nullptr;

    CustomButton* yesButton = nullptr;
    CustomButton* noButton = nullptr;

    std::function<void()> yesFunction;
    std::function<void()> noFunction;

    void createBackground();
    void createHeader();
    void createSubTitle();

    void createBottomButtons();

};


#endif //POPUPINGAME_H

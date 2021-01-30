//
// Created by emin on 30.01.2021.
//

#ifndef POPUP_H
#define POPUP_H

#include <cocos/2d/CCNode.h>

namespace cocos2d
{
    class Sprite;
}

class CustomButton;

class Popup : public cocos2d::Node
{
public:
    Popup();

protected:
    cocos2d::Sprite* layoutSprite = nullptr;
    cocos2d::Node* contentNode = nullptr;

    void fitCloseButton(const cocos2d::Rect& rect);
    void closePopup();
    void changeCloseButtonVisibility(const bool isVisible);

private:

    CustomButton* closeButton = nullptr;

    void createLayout();
    void createTouchListener();
    void createCloseButton();
};


#endif //POPUP_H

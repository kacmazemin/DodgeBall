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

class Popup : public cocos2d::Node
{
public:
    Popup();

protected:
    cocos2d::Sprite* backgroundSprite = nullptr;
    cocos2d::Node* contentNode = nullptr;


private:

    void createBackground();
    void createTouchListener();
    void createCloseButton();
};


#endif //POPUP_H

//
// Created by emin on 29.01.2021.
//

#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <cocos/2d/CCNode.h>

namespace cocos2d::ui
{
    class Button;
}

class CustomButton : public cocos2d::Node
{

public:
    CustomButton(const std::string& path, const cocos2d::Size& size);

    void setOnTap(const std::function<void()>& func);

    virtual cocos2d::Rect getBoundingBox() const ;

    void changeSoundActivity(const bool isEnable);
    void enableTintTo();

private:

    bool isSoundEffectEnable = true;
    float initialScale = .0f;
    std::string imagePath = "";
    cocos2d::Size size = cocos2d::Size::ZERO;

    cocos2d::Node* initialNode = nullptr;
    cocos2d::ui::Button* mainButton = nullptr;

    std::function<void()> function;

    void createButton();
    void playClickEffect();



};


#endif //CUSTOMBUTTON_H

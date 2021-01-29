//
// Created by emin on 29.01.2021.
//

#ifndef ANNOUNCERNODE_H
#define ANNOUNCERNODE_H

#include <cocos/2d/CCNode.h>

enum class AnnounceType
{
    GameStart = 0,
    Score = 1,
    Fail = 2,
    Win = 3,
    EndGame = 4,
    Undefined = 5

};
namespace cocos2d
{
    class Label;
}

class AnnouncerNode final : public cocos2d::Node
{
public:
    AnnouncerNode();

    void makeAnnounce(const AnnounceType type);

private:
    std::string stringContent = "";
    cocos2d::Size screenSize = cocos2d::Size::ZERO;

    AnnounceType announceType = AnnounceType::Undefined;
    cocos2d::Label* mainLabel = nullptr;

    void createMainLabel();
    void handleStringContent();


};


#endif //ANNOUNCERNODE_H

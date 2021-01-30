//
// Created by emin on 30.01.2021.
//

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "cocos2d.h"

class AudioManager
{
public:
    static AudioManager* getInstance();

    void playSoundEffect(const std::string &path, const float volume, const bool isLoop = false);
    void playButtonClick();

private:
    void init();
};


#endif //AUDIOMANAGER_H

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
    void playGamePlayMusic();
    void playMenuMusic();
    void playBallHitBallEffect();
    void playFailEffect();
    void playCueHitBall();

    void mute(const bool isMute);
    inline bool getIsMuted()
    {
        return isMuted;
    };

    void loadAssets();


private:

    int menuMusicId = 0;
    int gameMusicId = 0;

    bool isMuted = false;
    void init();
};


#endif //AUDIOMANAGER_H

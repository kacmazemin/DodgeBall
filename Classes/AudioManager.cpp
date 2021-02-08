//
// Created by emin on 30.01.2021.
//

#include "AudioManager.h"
#include "AudioEngine.h"

namespace
{
    //todo create new map and enum class then use only one function to call sound effects.
    const std::vector<std::string> assetPath{
            "Sounds/basic-click.wav",
            "Sounds/splash.wav",
            "Sounds/cue-hit-ball.wav",
            "Sounds/menu-music.wav",
            "Sounds/gameplay.wav",
            "Sounds/ball-hit-ball.wav",
            "Sounds/fail.wav"
            };
}

static AudioManager* sharedInstance = nullptr;

AudioManager* AudioManager::getInstance() {

    if (! sharedInstance)
    {
        sharedInstance = new AudioManager();
        sharedInstance->init();
    }

    return sharedInstance;
}

void AudioManager::init()
{

}

void AudioManager::playSoundEffect(const std::string &path, const float volume, const bool isLoop)
{
    if(!isMuted)
    {
        cocos2d::experimental::AudioEngine::play2d(path, isLoop, volume);
    }
}

void AudioManager::playButtonClick()
{
    if(!isMuted)
    {
        cocos2d::experimental::AudioEngine::play2d("Sounds/basic-click.wav", false, .6f);
    }
}

void AudioManager::playGamePlayMusic()
{
    cocos2d::experimental::AudioEngine::stop(menuMusicId);

    if(!isMuted)
    {
        gameMusicId = cocos2d::experimental::AudioEngine::play2d("Sounds/gameplay.wav",true,.6f);
    }
}


void AudioManager::playMenuMusic()
{
    cocos2d::experimental::AudioEngine::stop(gameMusicId);

    if(!isMuted)
    {
        menuMusicId = cocos2d::experimental::AudioEngine::play2d("Sounds/menu-music.wav", true, .6f);
    }
}

void AudioManager::loadAssets()
{
    for (const auto& path : assetPath)
    {
        cocos2d::experimental::AudioEngine::preload(path, [=](bool isSuccess)
        {
            if(isSuccess)
            {
                CCLOG("Sound preload is successful %s", path.c_str());

            }
            else
            {
                CCLOG("FAIL %s", path.c_str());
            }
        });
    }
}

void AudioManager::playBallHitBallEffect()
{
    if(!isMuted)
    {
        cocos2d::experimental::AudioEngine::play2d("Sounds/ball-hit-ball.wav", false, .6f);
    }
}

void AudioManager::playFailEffect()
{
    if(!isMuted)
    {
        cocos2d::experimental::AudioEngine::play2d("Sounds/fail.wav", false, .6f);
    }
}

void AudioManager::playCueHitBall()
{
    if(!isMuted)
    {
        cocos2d::experimental::AudioEngine::play2d("Sounds/cue-hit-ball.wav", false, .6f);
    }
}

void AudioManager::mute(const bool isMute)
{
    if(isMute)
    {
        isMuted = true;
        cocos2d::experimental::AudioEngine::stopAll();
    }
    else
    {
        isMuted = false;
        cocos2d::experimental::AudioEngine::resumeAll();

        cocos2d::experimental::AudioEngine::stop(menuMusicId);
        menuMusicId = cocos2d::experimental::AudioEngine::play2d("Sounds/menu-music.wav", true, .6f);

    }
}

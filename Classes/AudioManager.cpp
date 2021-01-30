//
// Created by emin on 30.01.2021.
//

#include "AudioManager.h"
#include "AudioEngine.h"

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
    //todo preload
}

void AudioManager::playSoundEffect(const std::string &path, const float volume, const bool isLoop)
{
    cocos2d::experimental::AudioEngine::play2d(path, isLoop, volume);
}

void AudioManager::playButtonClick()
{
    cocos2d::experimental::AudioEngine::play2d("Sounds/basic-click.wav", false, .6f);
}

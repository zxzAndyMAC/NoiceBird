#ifndef __SOUND_BIRD__
#define __SOUND_BIRD__

#include "SoundDispatcher.h"

class Sound;

static Sound* sound = NULL;

class Sound
{
public:
	inline static Sound* getInstance();
	inline void setDispatcher(SoundDispatcher* sd);
	inline void HandleSound();
private:
	SoundDispatcher* sd;
};

Sound* Sound::getInstance()
{
	if(NULL == sound)
		sound = new Sound();
	return sound;
}

void Sound::HandleSound()
{
	this->sd->SoundeHandler();
}

void Sound::setDispatcher(SoundDispatcher* sd)
{
	this->sd = sd;
}

#endif
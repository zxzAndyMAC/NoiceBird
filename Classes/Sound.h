#ifndef __SOUND_BIRD__
#define __SOUND_BIRD__

#include "SoundDispatcher.h"
#include "cocos2d.h"
USING_NS_CC;

class Sound
{
public:
	Sound():sd(NULL){};
	static Sound* getInstance();
	inline void setDispatcher(SoundDispatcher* sd);
	inline void HandleSound(float db);
	inline void EnableLeaderBoard(bool enable);
private:
	SoundDispatcher* sd;
};

void Sound::EnableLeaderBoard(bool enable)
{
	if(NULL == this->sd) return;
	this->sd->LeaderBoardEnable(enable);
} 

void Sound::HandleSound(float db)
{
	if(NULL == this->sd)
	{
		log("%s","SoundDispatcher is NULL");
		return;
	}
	this->sd->SoundeHandler(db);
}

void Sound::setDispatcher(SoundDispatcher* sd)
{
	if(NULL == sd)
	{
		log("%s", "SoundDispatcher can not be NULL!");
		return;
	}
	this->sd = sd;
}

#endif
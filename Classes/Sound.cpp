#include "Sound.h"

static Sound* sound = NULL;

Sound* Sound::getInstance()
{
	if(NULL == sound)
	{
		log("%s", "create a new sound!");
		sound = new Sound();
	}
	return sound;
}
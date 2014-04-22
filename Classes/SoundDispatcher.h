#ifndef __SOUND_DISA__
#define __SOUND_DISA__

class SoundDispatcher
{
public:
	virtual void SoundeHandler(float db) = 0;
};

#endif
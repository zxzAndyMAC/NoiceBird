#ifndef __ANDROID_BIRD_JNI_H__
#define __ANDROID_BIRD_JNI_H__

extern "C"
{
	extern void    startRecord();
	extern void    stopRecord();
	
	extern void    setAdsVisible(bool i);
	
	extern bool    startGoogle(int type);
	extern void    submitScore(int score, int type);
	extern void    showGoogle(int type);
	extern bool    googleenable();
	extern void    showin();
	
	extern void    googleRate();
};

#endif
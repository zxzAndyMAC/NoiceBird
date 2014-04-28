#ifndef __ANDROID_BIRD_JNI_H__
#define __ANDROID_BIRD_JNI_H__

extern "C"
{
	extern void    startRecord();
	extern void    stopRecord();
	
	extern void    setAdsVisible(bool i);
	
	extern bool    startGoogle();
	extern void    submitScore(int score);
	extern void    showGoogle();
	
	extern void    googleRate();
};

#endif
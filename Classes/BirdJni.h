#ifndef __ANDROID_BIRD_JNI_H__
#define __ANDROID_BIRD_JNI_H__

extern "C"
{
	extern void    startRecord();
	extern void    stopRecord();
	
	extern void    setAdsVisible(bool i);
};

#endif
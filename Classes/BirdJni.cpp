#include "BirdJni.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include <jni.h>

#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#include "Sound.h"
USING_NS_CC;
extern "C"
{
	void Java_com_origin_jni_jni_soundHandler(JNIEnv* env, jobject thiz, jfloat db)
	{
	//	LOGD("%s","Java_com_origin_jni_jni_soundHandler");
		float _db = db;
		Sound::getInstance()->HandleSound(_db);
	}
	
	void startRecord()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/jni",
			"startRecord",
			"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	
	void stopRecord()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/jni",
			"pauseRecord",
			"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	
	void setAdsVisible(bool i)
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/Ads",
			"setVisible",
			"(Z)V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, i);
			t.env->DeleteLocalRef(t.classID);
		}
	}
};
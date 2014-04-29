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
	
	void Java_com_origin_jni_google_login(JNIEnv* env, jobject thiz, jboolean enable)
	{
		bool en = enable;
		Sound::getInstance()->EnableLeaderBoard(en);
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
	
	void showin()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/Ads",
			"showin",
			"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	
	bool startGoogle(int type)
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/google",
			"start",
			"(I)Z"))
		{
			jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID, type);
			t.env->DeleteLocalRef(t.classID);
			return ret;
		}
		return false;
	}
	
	bool googleenable()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/google",
			"googleenable",
			"()Z"))
		{
			jboolean ret = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
			return ret;
		}
		return false;
	}
	
	void submitScore(int score, int type)
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/google",
			"sumbit",
			"(II)V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, score, type);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	
	void showGoogle(int type)
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/google",
			"show",
			"(I)V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID, type);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	
	void googleRate()
	{
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t,
			"com/origin/jni/google",
			"rate",
			"()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
	}
};
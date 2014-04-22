package com.origin.jni;

import com.origin.sound.RecordThread;

public class jni {
	private static RecordThread sound = null;
	public static boolean ifstarted = false;
	
	public static void createRecordThread()
	{
		sound = new RecordThread();
	}
	
	public static void startRecord()
	{
		ifstarted = true;
		if(null == sound)
			sound = new RecordThread();
		sound.start();
	}
	
	public static void pauseRecord()
	{
		sound.pause();
		sound = null;
	}
	
	public static void Handlesound(float db)
	{
		soundHandler(db);
	}
	
	private static native void soundHandler(float db);
}

package com.origin.sound;

import org.cocos2dx.lib.Cocos2dxHelper;

import com.origin.jni.jni;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.util.Log;

public class RecordThread extends Thread{
	private AudioRecord ar;  
    private int bs;  
    private static int SAMPLE_RATE_IN_HZ = 8000;  
    private boolean isRun = false;  
    double g = 0.0D;
    double s = 0.0D;
    
    public RecordThread() {  
        super();  
        bs = AudioRecord.getMinBufferSize(SAMPLE_RATE_IN_HZ,  
                AudioFormat.CHANNEL_CONFIGURATION_MONO,  
                AudioFormat.ENCODING_PCM_16BIT);  
        ar = new AudioRecord(MediaRecorder.AudioSource.MIC, SAMPLE_RATE_IN_HZ,  
                AudioFormat.CHANNEL_CONFIGURATION_MONO,  
                AudioFormat.ENCODING_PCM_16BIT, bs);  
    } 
        
    public void run() {  
        super.run();  
        ar.startRecording();   
        isRun = true;
        while(isRun){
            double d1 = 0.0D;
            short[] arrayOfShort = new short[bs];
            ar.read(arrayOfShort, 0, bs);
            int j = arrayOfShort.length;
            
            for (int i = 0; i < j; i++) {  
            	double d2 = Math.abs(arrayOfShort[i]);
            	d1 += d2 * d2;
            }
            

            {
            	double d3 = Math.sqrt(d1 / arrayOfShort.length);
                g = (20.0D * Math.log10(d3 / 32768.0D));
                final double d4 = 98.0D + g;
                if(Math.abs(s - d4)>1)
                {
                	s = d4;
                //	Log.d("Matrix", String.valueOf((int)d4));
                	final float db = (float) d4;
            		Cocos2dxHelper.runOnGLThread(new Runnable(){
        				@Override
        				public void run() {
        					// TODO Auto-generated method stub
        					jni.Handlesound(db);
        				}
            			
            		});
                }
            }
        }
        
        ar.stop();  
    }  
   
    public void pause() {  
                // 在调用本线程的 Activity 的 onPause 里调用，以便 Activity 暂停时释放麦克风  
        isRun = false;  
        try {
			super.join();
			join();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        ar.release();
        ar = null;
        Log.d("Matrix", "pause");
    }  
   
    public void start() {  
                // 在调用本线程的 Activity 的 onResume 里调用，以便 Activity 恢复后继续获取麦克风输入音量  
        if (!isRun) {  
        	Log.d("Matrix", "start");
            super.start();  
        }  
    } 
}

/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.origin.noicebird;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Intent;
import android.os.Bundle;
 
import com.inmobi.commons.InMobi;
import com.inmobi.commons.InMobi.LOG_LEVEL;
import com.inmobi.monetization.IMInterstitial;
import com.origin.jni.Ads;
import com.origin.jni.google;
import com.origin.jni.jni;


public class AppActivity extends Cocos2dxActivity {

	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		InMobi.initialize(this, "25c29a0fb759402fac0acff2e163f79c");
		//InMobi.setLogLevel(LOG_LEVEL.DEBUG);
		super.onCreate(savedInstanceState);
		google.initGoogle(this);
		
		Ads.interstitial = new IMInterstitial(this, "25c29a0fb759402fac0acff2e163f79c");
		Ads.interstitial.loadInterstitial();
	}
	
	@Override
	public void onResume()
	{
		super.onResume();
		if(jni.ifstarted)
			jni.startRecord();
	}
	
	@Override
	public void onPause()
	{
		super.onPause();
		if(jni.ifstarted)
			jni.pauseRecord();
	}
	
	@Override
	protected void onStop() {
	    super.onStop();
	    google.stop();
	}

	@Override
	protected void onActivityResult(int request, int response, Intent data) {
	    super.onActivityResult(request, response, data);
	    google.onActivityResult(request, response, data);
	}
}

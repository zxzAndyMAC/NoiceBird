package com.origin.jni;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.util.Log;
import android.view.View;

import com.inmobi.monetization.IMBanner;
import com.inmobi.monetization.IMInterstitial;

public class Ads {
	public static IMBanner banner = null;
	public static IMInterstitial interstitial = null;
	
	public static void setVisible(boolean i)
	{
		if(null == banner) return;
		final boolean visible = i;
		Cocos2dxHelper.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(visible)
					banner.setVisibility(View.VISIBLE);
				else
					banner.setVisibility(View.GONE);
			}});
	}
	
	public static void showin()
	{
		Cocos2dxHelper.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if (interstitial.getState() ==IMInterstitial.State.READY)
				{
					Log.d("cocos2d-x debug info", "interstitial.getState() ==IMInterstitial.State.READY");
					interstitial.show();
				}
				else if(interstitial.getState() ==IMInterstitial.State.INIT)
				{
					Log.d("cocos2d-x debug info", "interstitial.getState() ==IMInterstitial.State.INIT");
					interstitial.loadInterstitial();
				}
			}});
	}
}

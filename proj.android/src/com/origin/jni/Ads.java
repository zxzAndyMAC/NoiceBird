package com.origin.jni;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.view.View;

import com.inmobi.monetization.IMBanner;

public class Ads {
	public static IMBanner banner = null;
	
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
}

package com.origin.jni;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.util.Log;

import com.google.android.gms.games.Games;
import com.google.example.games.basegameutils.GameHelper;
import com.google.example.games.basegameutils.GameHelper.GameHelperListener;

public class google {
	private static GameHelper mHelper = null;
	private static Activity app;
	private static boolean isShow = false;
	private static int stype = 1;
	private static boolean failed = false;
	
	public static void initGoogle(Activity a)
	{
		app = a;
		mHelper = new GameHelper(app, GameHelper.CLIENT_GAMES);
		mHelper.enableDebugLog(true);
		GameHelperListener listener = new GameHelper.GameHelperListener() {
	        @Override
	        public void onSignInSucceeded() {
	            // handle sign-in succeess
	        	isShow = true;
	        	failed = false;
	        	login(true);
	        	show(stype);
	        }
	        @Override
	        public void onSignInFailed() {
	            // handle sign-in failure (e.g. show Sign In button)
	        	login(false);
	        	isShow = false;
	        	failed = true;
	        }

	    };
	    mHelper.setup(listener);
	}
	
	public static boolean start(int type)
	{
		if(failed)
		{
			stype = type;
			mHelper.reconnectClient();
			return false;
		}
		if(!isShow)
		{
			stype = type;
			mHelper.onStart(app);
			return false;
		}
		return true;
	}
	
	public static boolean googleenable()
	{
		return isShow;
	}
	
	public static void stop()
	{
		if(null != mHelper)
			mHelper.onStop();
	}
	
	public static void onActivityResult(int request, int response, Intent data) {
		// TODO Auto-generated method stub
		if(null != mHelper)
			mHelper.onActivityResult(request, response, data);
	}
	
	public static void show(int type)
	{
		Log.d("cocos2d-x debug info", "show Leaderboards");
		final int t = type;
		Cocos2dxHelper.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(1 == t)
					app.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mHelper.getApiClient(), "CgkIiI6vte0DEAIQAQ"), 100);
				else
					app.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mHelper.getApiClient(), "CgkIiI6vte0DEAIQBw"), 100);
			}
			
		});
	}
	
	public static void rate()
	{
		Cocos2dxHelper.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				final String appPackageName = Cocos2dxHelper.getActivity().getPackageName(); // getPackageName() from Context or Activity object
				try {
					Cocos2dxHelper.getActivity().startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("market://details?id=" + appPackageName)));
				} catch (android.content.ActivityNotFoundException anfe) {
					Cocos2dxHelper.getActivity().startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("http://play.google.com/store/apps/details?id=" + appPackageName)));
				}
			}
			
		});
	}
	
	private static void sumbit(int score, int type)
	{
		Log.d("cocos2d-x debug info", "sumbit() score");
		final int s = score;
		final int t = type;
		Cocos2dxHelper.getActivity().runOnUiThread(new Runnable(){

			@Override
			public void run() {
				// TODO Auto-generated method stub
				if(1 == t)
					Games.Leaderboards.submitScore(mHelper.getApiClient(), "CgkIiI6vte0DEAIQAQ", s);
				else
					Games.Leaderboards.submitScore(mHelper.getApiClient(), "CgkIiI6vte0DEAIQBw", s);
			}
			
		});
	}
	
	private static native void login(boolean success);

	
}

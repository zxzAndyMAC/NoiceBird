package com.origin.jni;

import android.app.Activity;
import android.content.Intent;

import com.google.android.gms.games.Games;
import com.google.example.games.basegameutils.GameHelper;
import com.google.example.games.basegameutils.GameHelper.GameHelperListener;

public class google {
	private static GameHelper mHelper = null;
	private static Activity app;
	private static boolean isShow = false;
	
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
	        	login(true);
	        }
	        @Override
	        public void onSignInFailed() {
	            // handle sign-in failure (e.g. show Sign In button)
	        }

	    };
	    mHelper.setup(listener);
	}
	
	public static boolean start()
	{
		if(!isShow)
		{
			mHelper.onStart(app);
			return false;
		}
		return true;
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
	
	public static void show(int score)
	{
		app.startActivityForResult(Games.Leaderboards.getLeaderboardIntent(mHelper.getApiClient(), "CgkIiI6vte0DEAIQAQ"), 100);
	}
	
	private static void sumbit(int score)
	{
		Games.Leaderboards.submitScore(mHelper.getApiClient(), "CgkIiI6vte0DEAIQAQ", score);
	}
	
	private static native void login(boolean success);

	
}

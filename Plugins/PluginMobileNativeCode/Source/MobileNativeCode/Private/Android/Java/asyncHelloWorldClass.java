package com.Plugins.MobileNativeCode;//Use only this package, do not change it!!!

import android.app.Activity;
import android.support.annotation.Keep;
import java.lang.Thread;

@Keep
public class asyncHelloWorldClass {

	//Calling *.cpp code
	@Keep
	public static native void CallBackCppAndroid(String returnStr);

	// Calling Java code asynchronously and returning the value back to C++
	@Keep
	public static void asyncHelloWorldOnAndroid(final Activity activity, final String text, final int delay) {
// 		
// 		activity.runOnUiThread(new Runnable() {
// 			@Override
// 			public void run()
// 			{
// 				CallBackCppAndroid(text+" on Android modified with delay " + delay);
// 			}
// 		});
		
		
		
        Thread testThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(delay);
                    activity.runOnUiThread(new Runnable() {
                        @Override
                        public void run()
                        {
                            CallBackCppAndroid(text+" on Android modified with delay " + delay);
                        }
                    });
                } catch (Exception e) {
                }
            }
        });
        testThread.start();
	}
	
	

}



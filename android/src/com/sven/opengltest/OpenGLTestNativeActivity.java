package com.sven.opengltest;

import android.app.NativeActivity;

public class OpenGLTestNativeActivity extends NativeActivity {
	
	
	
	static {
		android.os.Debug.waitForDebugger();
		System.loadLibrary("gnustl_shared");
	}	
	
}

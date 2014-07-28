#include "applicationandroid.h"

#include "assert.h"

#include <android_native_app_glue.h>

#include <assets/loaderandroid.h>

#include "logging.h"

static void handleAppCmdFuncPtr(struct android_app* app, int32_t cmd) {
	ApplicationAndroid* application = static_cast<ApplicationAndroid*>(app->userData);

	if(nullptr != application){
		application->handleAppCmd(cmd);
	} else{
		// User data should be set to a valid application pointer
		LOG(FATAL) << "handleAppCmd() hasn't found a valid userData pointer.";
	}
}

static int32_t handleInputEventFuncPtr(struct android_app* app, AInputEvent* event) {
	ApplicationAndroid* application = static_cast<ApplicationAndroid*>(app->userData);

	if(nullptr != application){
		if(application->handleInputEvent(event)){
			return 1;
		}
	} else{
		// User date should be set to a valid application pointer
		LOG(FATAL) << "handleInputEvent() hasn't found a valid userData pointer.";
	}

	return 0;
}

ApplicationAndroid::ApplicationAndroid(android_app* app)
	: Application()
	, app(app)
	, surface(EGL_NO_SURFACE)
	, display(EGL_NO_DISPLAY)
	, context(EGL_NO_CONTEXT)
{
	getAssetManager().setAssetLoader(new Assets::LoaderAndroid(app->activity->assetManager));
}
ApplicationAndroid::~ApplicationAndroid()
{

}

bool ApplicationAndroid::init()
{
	assert(nullptr != app);

	if ( nullptr != app->savedState) {
		// We are starting with a previous saved state; restore from it.
	    LOG(INFO) << "Saved state detected";
	}

	app->userData = this;	//State user data

	app->onAppCmd = handleAppCmdFuncPtr;	// AppCmdb Callback
	app->onInputEvent = handleInputEventFuncPtr;	// InputEvent Callback

	return true;
}

void ApplicationAndroid::handleEvents()
{
	int ident;
	int events;
	struct android_poll_source* source;

	while ((ident=ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0) {

		// Process this event.
		if (source != NULL) {
			source->process(app, source);
	    }
		// Check if we are exiting.
	    if (app->destroyRequested != 0) {

	  		return;
		}
	}
}

void ApplicationAndroid::postRender()
{
	eglSwapBuffers(display, surface);
}

void ApplicationAndroid::handleAppCmd(int32_t cmd)
{
	switch (cmd) {
		case APP_CMD_SAVE_STATE:
			// The system has asked us to save our current state.  Do so.
	        //engine->app->savedState = malloc(sizeof(struct saved_state));
	        //*((struct saved_state*)engine->app->savedState) = engine->state;
	        //engine->app->savedStateSize = sizeof(struct saved_state);
	        LOG(INFO) << "APP Cmd Save State";
	        break;
		case APP_CMD_INIT_WINDOW:
	            // The window is being shown, get it ready.
	            if (app->window != NULL) {
	            	initWindow();
	            }
	        	__android_log_print(ANDROID_LOG_INFO, "OpenGLTestActivity", "APP Cmd Init Window");
	            break;
	        case APP_CMD_TERM_WINDOW:
	            // The window is being hidden or closed, clean it up.
	        	LOG(INFO) << "APP Cmd Terminate Window";
	        	destroyWindow();
	            break;
	        case APP_CMD_GAINED_FOCUS:
	            // When our app gains focus, we start monitoring the accelerometer.
	//            if (engine->accelerometerSensor != NULL) {
	//                ASensorEventQueue_enableSensor(engine->sensorEventQueue,
	//                        engine->accelerometerSensor);
	//                // We'd like to get 60 events per second (in us).
	//                ASensorEventQueue_setEventRate(engine->sensorEventQueue,
	//                        engine->accelerometerSensor, (1000L/60)*1000);
	//            }
	        	LOG(INFO) << "APP Cmd Focus gained";
	            break;
	        case APP_CMD_LOST_FOCUS:
	//            // When our app loses focus, we stop monitoring the accelerometer.
	//            // This is to avoid consuming battery while not being used.
	//            if (engine->accelerometerSensor != NULL) {
	//                ASensorEventQueue_disableSensor(engine->sensorEventQueue,
	//                        engine->accelerometerSensor);
	//            }
	//            // Also stop animating.
	//            engine->animating = 0;
	//            engine_draw_frame(engine);
	        	LOG(INFO) << "APP Cmd Focus lost";
	            break;
	}
}

bool ApplicationAndroid::handleInputEvent(AInputEvent* event)
{
	return false;
}

void ApplicationAndroid::initWindow(){
	const EGLint attribs[] = {
		            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		            EGL_BLUE_SIZE, 8,
		            EGL_GREEN_SIZE, 8,
		            EGL_RED_SIZE, 8,
		    		EGL_ALPHA_SIZE, 8,
		            EGL_STENCIL_SIZE, 8,
		            EGL_DEPTH_SIZE, 24,
		            EGL_NONE
		 };

		const EGLint context_attrib_list[] = {
				EGL_CONTEXT_CLIENT_VERSION, 3,
				EGL_NONE
		};
		    EGLint w, h, format;
		    EGLint numConfigs;
		    EGLConfig config;

		    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);


		    EGLint major, minor;

		    if (eglInitialize(display, &major, &minor) == EGL_TRUE) {
		    	LOG(INFO) << "Initialized EGL Version "<< major << "." << minor;
		    } else{
		    	LOG(ERROR) << "Error initializing EGL.";
		    	return;
		    }

		    EGLBoolean result = eglChooseConfig(display, attribs, &config, 1, &numConfigs);

		    if (result != EGL_TRUE) {
		    	LOG(ERROR) << "Error choosing EGL config.";
		    	return;
		    }

		    EGLint out;
		    eglGetConfigAttrib(display, config, EGL_BUFFER_SIZE, &out);
		    LOG(DEBUG) << "EGL_BUFFER_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_ALPHA_SIZE, &out);
		    LOG(DEBUG) << "EGL_ALPHA_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &out);
		    LOG(DEBUG) << "EGL_BLUE_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &out);
		    LOG(DEBUG) << "EGL_GREEN_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_RED_SIZE, &out);
		    LOG(DEBUG) << "EGL_RED_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &out);
		    LOG(DEBUG) << "EGL_DEPTH_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_STENCIL_SIZE, &out);
		    LOG(DEBUG) << "EGL_STENCIL_SIZE = " << out;

		    eglGetConfigAttrib(display, config, EGL_LEVEL, &out);
		    LOG(DEBUG) << "EGL_LEVEL = " << out;

		    eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_HEIGHT, &out);
		    LOG(DEBUG) << "EGL_MAX_PBUFFER_HEIGHT = " << out;

		    eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_WIDTH, &out);
		    LOG(DEBUG) << "EGL_MAX_PBUFFER_WIDTH = " << out;

		    eglGetConfigAttrib(display, config, EGL_MAX_PBUFFER_PIXELS, &out);
		    LOG(DEBUG) << "EGL_MAX_PBUFFER_PIXELS = " << out;

		    eglGetConfigAttrib(display, config, EGL_SAMPLES, &out);
		    LOG(DEBUG) << "EGL_SAMPLES = " << out;

		    eglGetConfigAttrib(display, config, EGL_SAMPLE_BUFFERS, &out);
		    LOG(DEBUG) << "EGL_SAMPLE_BUFFERS = " << out;

		    eglGetConfigAttrib(display, config, EGL_COLOR_BUFFER_TYPE, &out);
		    LOG(DEBUG) << "EGL_COLOR_BUFFER_TYPE = " << out;


		    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

		    ANativeWindow_setBuffersGeometry(app->window, 0, 0, format);

		    surface = eglCreateWindowSurface(display, config, app->window, NULL);

		    context = eglCreateContext(display, config, EGL_NO_CONTEXT, context_attrib_list);

		    if(EGL_NO_CONTEXT == context){
		    	LOG(ERROR) << "Could not create OpenGL ES 3 context.";
		    	return;
		    }

		    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
		    		LOG(ERROR) << "Unable to make context " << context << " current.";
		            return;
		    }

		    // Query width and height
		    eglQuerySurface(display, surface, EGL_WIDTH, &w);
		    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

		    LOG(DEBUG) << "Surface dimensions = " << w << " x " << h << ".";

		    setScreenSize(w,h);

			//const GLubyte* versionStrByte =
			const char* versionStr = (const char *) glGetString(GL_VERSION);
			LOG(INFO) << "OpenGL ES version = " << versionStr;

			//		versionStr = glGetString(GL_VENDOR);
			//		__android_log_print(ANDROID_LOG_INFO, "OpenGLTestActivity", versionStr);
			//		versionStr = glGetString(GL_RENDERER);
			//		__android_log_print(ANDROID_LOG_INFO, "OpenGLTestActivity", versionStr);
			//		versionStr = glGetString(GL_EXTENSIONS);
			//		__android_log_print(ANDROID_LOG_INFO, "OpenGLTestActivity", versionStr);

					//__android_log_print(ANDROID_LOG_INFO, "OpenGLTestActivity", "Set Viewport");
			glViewport(0, 0, w, h);

			getRenderer().setScreenSize(getScreenSize());

			if( !getRenderer().init() ){
				LOG(ERROR) << "Renderer initialization failed.";
			}

			createObjects(); // ToDo: Wrong place
}

void ApplicationAndroid::destroyWindow(){
	if (display != EGL_NO_DISPLAY) {
	        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	        if (context != EGL_NO_CONTEXT) {
	            eglDestroyContext(display, context);
	        }
	        if (surface != EGL_NO_SURFACE) {
	            eglDestroySurface(display, surface);
	        }
	        eglTerminate(display);
	    }
	    display = EGL_NO_DISPLAY;
	    context = EGL_NO_CONTEXT;
	    surface = EGL_NO_SURFACE;
}

bool ApplicationAndroid::needsUpdate(){
	return app->window != nullptr;
}

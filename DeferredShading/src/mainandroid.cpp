#include "applicationandroid.h"

#include <android_native_app_glue.h>

#include <unistd.h>

//#include <jni.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "plattformopengl.h"

#include <logging.h>

#include <android/log.h>

_INITIALIZE_EASYLOGGINGPP

// Fix for easylogging
int elToAndroidLog(el::Level priority){
	switch (priority){
	case el::Level::Trace:
		return ANDROID_LOG_DEFAULT;
	case el::Level::Verbose:
		return ANDROID_LOG_VERBOSE;
	case el::Level::Debug:
		return ANDROID_LOG_DEBUG;
	case el::Level::Info:
		return ANDROID_LOG_INFO;
	case el::Level::Warning:
		return ANDROID_LOG_WARN;
	case el::Level::Error:
		return ANDROID_LOG_ERROR;
	case el::Level::Fatal:
		return ANDROID_LOG_FATAL;
	case el::Level::Unknown:
	case el::Level::Global:
		return ANDROID_LOG_UNKNOWN;
	}
	return ANDROID_LOG_UNKNOWN;
}

/* Start up the SDL app */
void android_main(struct android_app* state)
{

    el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format, "%msg");

	LOG(ERROR) << "Hey look its easylogging";

	LOG(INFO) << "Entering AndroidMain";

    // Make sure glue isn't stripped.
    app_dummy();

    ApplicationAndroid app(state);

    app.init();

    app.exec();

    //state->activity->vm->DetachCurrentThread();
}


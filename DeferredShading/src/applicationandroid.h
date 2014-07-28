#pragma once

#include "application.h"

#include "EGL/egl.h"

class AInputEvent;

struct android_app;

class ApplicationAndroid : public Application{

public:

	ApplicationAndroid(android_app* app);
	virtual ~ApplicationAndroid();

    virtual bool init();

    void handleAppCmd(int32_t cmd);

    bool handleInputEvent(AInputEvent* event);

private:

    virtual void handleEvents();

    virtual void postRender();

    virtual bool needsUpdate();

    void initWindow();
    void destroyWindow();

    android_app* app;

    EGLSurface surface;
    EGLDisplay display;
    EGLContext context;

};

#pragma once

#include "application.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>


class ApplicationDesktop : public Application {

public:

    ApplicationDesktop(unsigned int newWidth, unsigned int newHeight);
    virtual ~ApplicationDesktop();

    virtual bool init();

private:

    virtual void handleEvents();

    virtual void postRender();

    // Application window
    SDL_Window *mainwindow;
    // Application render context   //ToDo: Move to renderer
    SDL_GLContext maincontext;

};

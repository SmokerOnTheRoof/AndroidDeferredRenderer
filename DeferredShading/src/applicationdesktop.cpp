#include "applicationdesktop.h"

#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include <logging.h>

#include <glm/gtc/type_ptr.hpp>

#include <assets/loaderdesktop.h>

ApplicationDesktop::ApplicationDesktop(unsigned int newWidth, unsigned int newHeight)
    : Application(newWidth, newHeight)
    , mainwindow(nullptr)
    , maincontext(0)
{
    getAssetManager().setAssetLoader(new Assets::LoaderDesktop());
}

ApplicationDesktop::~ApplicationDesktop()
{
    if(nullptr != maincontext){
        SDL_GL_DeleteContext(maincontext);
    }
    if(0 != mainwindow){
        SDL_DestroyWindow(mainwindow);
    }
    // Shutdown SDL
    SDL_Quit();
}

bool ApplicationDesktop::init()
{
    if(SDL_Init(0) < 0){
        // ToDo: Error handling
    }

    // ToDo: Maybe this stuff will be moved back to renderer
    //       in this case ther would be a renderer for desktop and android

    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0){ /* Initialize SDL's Video subsystem */
        LOG(ERROR) << "SDL Video subsystem could not been initialized.";
        return false;
    }

    //Request opengl 4.2 context.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
 
    //Turn on double buffering with a 24bit Z buffer.
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // R8G8B8A8
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Create the window
    mainwindow = SDL_CreateWindow("OpenGLTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        getScreenSize().x, getScreenSize().y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow){ /* Die if creation failed */
        LOG(ERROR) << "Main window could not been created" << std::endl;
        return false;
    }

   // create the OpenGL context
    maincontext = SDL_GL_CreateContext(mainwindow);

    // Swap in sync with the refresh rate
    SDL_GL_SetSwapInterval(1);

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        LOG(ERROR) << "Glew initialization failed.";
        return false;
    }

    const GLubyte* versionStr = glGetString(GL_VERSION);

    LOG(INFO) << "OpenGL Version = " << versionStr;

    if( !getRenderer().init() ){
        return false;
    }

    createObjects();

    return true;
}

void ApplicationDesktop::postRender(){
    SDL_GL_SwapWindow(mainwindow);
}

void ApplicationDesktop::handleEvents()
{
    SDL_Event event;

    while( SDL_PollEvent(&event)){
        switch(event.type)
        {
        case SDL_QUIT:
            exit();
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.scancode){
            case SDL_SCANCODE_0:
                getRenderer().setActiveTexture(0);
                break;
            case SDL_SCANCODE_1:
                getRenderer().setActiveTexture(1);
                break;
            case SDL_SCANCODE_2:
                getRenderer().setActiveTexture(2);
                break;
            case SDL_SCANCODE_3:
                getRenderer().setActiveTexture(3);
                break;
            case SDL_SCANCODE_4:
                getRenderer().setActiveTexture(4);
                break;
            case SDL_SCANCODE_5:
                getRenderer().setActiveTexture(5);
                break;
            case SDL_SCANCODE_6:
                getRenderer().setActiveTexture(6);
                break;
            case SDL_SCANCODE_7:
                getRenderer().setActiveTexture(7);
                break;
            case SDL_SCANCODE_8:
                getRenderer().setActiveTexture(8);
                break;
            case SDL_SCANCODE_9:
                getRenderer().setActiveTexture(9);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

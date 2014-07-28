#pragma once

#define SDL_MAIN_HANDLED

#include "plattformopengl.h"

#include <vector>

#include "render/primitives/cube.h"

#include <render/renderer.h>
#include <animation/manager.h>

#include <assets/manager.h>

#include "timer.h"

/** \class Application
 *  \brief This class represents the Application.
 *
 *  This is the application class. The main purpose of this class is to
 *  represent the whole application. The main loop runs in this class,
 *  event will be fetched and all OS calls will be processed here.
 *  
 *  Every supported platforms has it's own Application subclass.
 */

class Application{

public:

	Application();
    Application(unsigned int newWidth, unsigned int newHeight);
    virtual ~Application();

    /**
     *	\brief Enters the application loop.
     *
     *	Enter the application loop. Will quit only when the application quits.
     *
     *  /return Returns 0 on success.
     */
    int exec();

    /**
     *	\brief Stops the rendering loop.
     */
    void stopRendering(){contRendering = false;};

    /**
     *	\brief Returns the renderer of the application.
     *
     *	\return The applications renderer.
     */
    Render::Renderer &getRenderer(){return renderer;};

    /**
     *	\brief Returns animation manager of the application.
     *
     *	\return The applications animation manager.
     */
    Animation::Manager &getAnimationManager(){return animationManager;}

    /**
     *	\brief Initializes the application.
     *
     *	Returns true if initialization was succesfull.
     *
     *	\return True on success, False otherwise.
     */
    virtual bool init() = 0;

    /**
     *	\brief Returns the screen size of the applications window.
     *
     *	\return glm::uvec2 which contains the windows dimensions.
     */
    glm::uvec2& getScreenSize(){return screenSize;}

    /**
     *	\brief Sets the screen size of the applications window.
     *
     *	\param width New width of the applications window.
     *	\param height New heigt of the applications window.
     */
    void setScreenSize(unsigned int width, unsigned int height){
    	screenSize = glm::uvec2(width, height);
    }

    /**
     *	\brief Exits the application.
     */
    virtual void exit(){stopRendering();}

    /**
     *	\brief Returns the asset manager.
     *
     *	\return Ref to the application's AssetManager.
     */
    Assets::Manager& getAssetManager(){return assetManager;}

    /**
     *	\brief Set up the scene.
     */
    virtual void createObjects();

private:

    virtual void handleEvents() {};

    /**
     *	\brief This method gets called after rendering is finished.
     *
     *	In your sub classed application this is the place
     *  where you will swap the buffers.
     */
    virtual void postRender(){};

    virtual bool needsUpdate(){return true;};

    bool contRendering;
    
    glm::uvec2 screenSize;

    Render::Renderer renderer;

    Animation::Manager animationManager;

    Timer timer;

    Assets::Manager assetManager;

};

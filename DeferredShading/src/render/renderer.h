#pragma once

#include <vector>
#include <memory>

#include "rendertarget.h"
#include "gbuffer.h"
#include "directionallight.h"

#include <glm/glm.hpp>


namespace Render{

// Forward declaration
class Object;
//class DirectionalLight;
class Camera;

/** \class Renderer
 *  \brief The heart of the deferred rendering.
 *
 *  The renderer is responsible for storing all objects which
 *  should be rendered and also every light source.
 *
 *  The renderer also contains the render function.
 *
 */

class Renderer : public RenderTarget{

public:

    Renderer(glm::uvec2 newScreenSize);
    ~Renderer();

    /**
	 * Reimplemented from RenderTarget
     */

    virtual glm::uvec2 getDimensions(){return screenSize;}

    /**
     *	\brief Adds an object to the render list.
     *
     *	/param object shared pointer ref to the object which should be added
     */
    void addObject(const std::shared_ptr<Object>& object){objectList.push_back(object);}

    /**
     *	\brief Initializes the renderer.
     *
     */
    bool init();

    /**
     *	\brief Render the scene.
     *
     */
    void render();

    /**
     *	\brief Set the dimension of the render window.
     *
     *	/param newScreenSize Reference to a vec2 which contains the screen size.
     */
    void setDimensions(const glm::vec2& newScreenSize){screenSize = newScreenSize;};

    /**
     *	\brief Sets the current active texture.
     *
     *  This method is for debugging purposes only.
     *  Switches the active GBuffer texture.
     *  The possible values are:
     *  
     *  0(default)  The composite output.
     *  1           World Position
     *  2           Diffuse color
     *  3           Normal
     *
     *	/param newState The value of the Texture.
     */
    void setActiveTexture(unsigned int newState);

    /**
     *	\brief Switches to the next texture in order.
     *
     *	/see setActiveTexture()
     */
    void incrActiveTexture();

    /**
     *	\brief Adds an camera to the camera list.
     *
     *	/param camera Shared pointer ref to an camera object.
     */
    void addCamera(const std::shared_ptr<Camera>& camera){activeCameras.push_back(camera);}

    /**
     *	\brief Adds a light to the scene.
     *
     *	/param light Shared pointer ref to a light object.
     */
    void addLight(const std::shared_ptr<DirectionalLight>& light)
    {
        light->setScreenSize(screenSize);
        lightsList.push_back(light);
    }

    /**
     *	\brief Sets the screen size of the application window.
     *
     *	/param width	Width of the application window.
     *	/param height 	Height of the application window.
     */
    void setScreenSize(unsigned int width, unsigned int height)
    {
    	screenSize =  glm::uvec2(width, height);
    }

    /**
     *	\brief Sets the screen size of the application window.
     *
     *	/param newScreenSize glm::uvec2 dimension vector of the window.
     */
    void setScreenSize(const glm::uvec2 &newScreenSize)
    {
    	screenSize =  newScreenSize;
    }

private:

    void renderGeometryPass(Render::Camera& camera);

    void renderLightPass(Render::Camera& camera);


    std::vector< std::shared_ptr<Object> > objectList;

    std::vector< std::shared_ptr<DirectionalLight> > lightsList; // lights list

    GBuffer gBuffer;

    std::vector< std::shared_ptr<Render::Camera> > activeCameras;    // ToDo: Aka active render targets

    // The active deferred stage
    unsigned int activeRenderState; // ToDo: For now this is a feature
                                    // should be used for debugging later

    glm::uvec2 screenSize;

};



}

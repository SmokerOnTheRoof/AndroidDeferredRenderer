#include "renderer.h"

#include "plattformopengl.h"

#include "object.h"

#include "camera.h"
#include "directionallight.h"

#include "logging.h"

namespace Render{

Renderer::Renderer( glm::uvec2 newScreenSize )
    : objectList()
    , lightsList()
    , gBuffer()
    , activeCameras()
    , activeRenderState(0)
    , screenSize(newScreenSize)
{

}

Renderer::~Renderer()
{

}

bool Renderer::init()
{
    gBuffer.setDimensions(screenSize.x, screenSize.y);
    gBuffer.addLayer(GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE, "colorMap");
    gBuffer.addLayer(GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE, "normalVSMap");
    //gBuffer.addLayer(GL_RG_INTEGER, GL_RG16UI, GL_UNSIGNED_SHORT, "normalVSMap");

    if( gBuffer.init() ){
        LOG(INFO) << "GBuffer initialized successfully, with depth of "
            << gBuffer.getSize();
    } else{
        LOG(ERROR) << "Error initializing GBuffer";
        return false;
    }

    return true;
}

void Renderer::render()
{

    for(auto cameraIter = activeCameras.begin(); cameraIter < activeCameras.end(); cameraIter++){
        (*cameraIter)->update();

    // Geometry pass
    renderGeometryPass( **cameraIter );
    // light pass
    renderLightPass( **cameraIter );
    
    }
}

void Renderer::renderGeometryPass(Render::Camera& camera)
{
    // Set the clear color to some dark grey
    glClearColor ( 0.1f, 0.1f, 0.1f, 1.0f );

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gBuffer.bindForWriting();

    glDepthMask(GL_TRUE);

    // Set the clear color to black
    glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glDisable(GL_BLEND);

    // Update the view and projection matrices from the camera

    // Render all objects
    for(auto iter=objectList.begin(); iter!=objectList.end(); iter++){
        (*iter)->update(camera);
        (*iter)->render();
    }

    glDepthMask(GL_FALSE);

    glDisable(GL_DEPTH_TEST);
}

void Renderer::renderLightPass(Render::Camera& camera)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(activeRenderState > 0){
        gBuffer.bindForReading();
        gBuffer.setReadBuffer(activeRenderState-1);
        glBlitFramebuffer(0, 0, screenSize.x, screenSize.y, 0, 0, screenSize.x, screenSize.y, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    } else{

        // Enable blending

        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_ONE, GL_ONE);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind the gbuffer

        gBuffer.bindForLightPass();
        
        for(auto lightIter = lightsList.begin(); lightIter < lightsList.end(); lightIter++){
            (*lightIter)->update(camera);
            (*lightIter)->render();
        }

    }
}

void Renderer::setActiveTexture( unsigned int newState )
{
    if(newState <= gBuffer.getSize()){
        activeRenderState = newState;
        std::cout<< "Switched to state " << activeRenderState << std::endl;
    }
}

void Renderer::incrActiveTexture()
{
    activeRenderState++;
    if(activeRenderState >= gBuffer.getSize()){
        activeRenderState = 0;
    }
}

}

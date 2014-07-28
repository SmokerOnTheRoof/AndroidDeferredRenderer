#pragma once

#include "plattformopengl.h"

#include <vector>
#include <string>

/** \class GBuffer
 *  \brief The GBuffer.
 *
 *  This class represents the GBuffer which is needed for 
 *  deferred shading. For now the GBuffer is easy to configure,
 *  to allow further expansion if additional render information
 *  are needed. But with further development the GBuffer needs to
 *  be optimized to reduce memory.
 *
 */

class GBuffer {

public:

    GBuffer();
    ~GBuffer();
    /**
     *	\brief Sets the size (layers) of the gbuffer.
     *
     *	\param newSize New gbuffer depth.
     *
     */
    void setSize(unsigned int newSize);

    /**
     *	\brief Returns the size (layers) of the gbuffer.
     *
     *	\return The gbuffer's depth.
     */
    unsigned int getSize();

    /**
     *	\brief Sets the Dimensions of the gbuffer.
     *
     *	\param newWidth The gbuffers width.
     *	\param newHeight The gbuffers height.
     *
     */
    void setDimensions(unsigned int newWidth, unsigned int newHeight){width=newWidth; height=newHeight;}

    /**
     *	\brief Binds the gbuffer for reading.
     */
    void bindForWriting();

    /**
     *	\brief Binds the gbuffer for writting.
     */
    void bindForReading();

    /**
     *	\brief Bind the gbuffer for the light pass.
     */
    void bindForLightPass();

    /**
     *	\brief Sets the gbuffer layer which should be read.
     *
     *	\param buffer Index of the gbuffer layer.
     */
    void setReadBuffer(unsigned int buffer);

    /**
     *	\brief Sets the layer at index to the given format.
     *
     *	Must be called before init.
     *
     *	\param index 			Index of the gbuffer layer.
     *	\param format 			Format to use.
     *	\param formatInternal 	Internal format to use.
     *	\param type 			Type to use.
     *	\param name 			Name of the layer
     */
    void setLayer(size_t index, GLenum format, GLenum formatInternal, GLenum type, std::string name);

    /**
     *	\brief Adds an layer to the gbuffer with the given format.
     *
     *	Must be called before init.
     *
     *	\param format 			Format to use.
     *	\param formatInternal 	Internal format to use.
     *	\param type 			Type to use.
     *	\param name 			Name of the layer
     */
    void addLayer(GLenum format, GLenum formatInternal, GLenum type, std::string name);

    /**
     *	\brief Initializes the gbuffer.
     */
    bool init();

private:

    GLuint framebuffer;
    // ToDo: Maybe add a GBufferLayer class
    std::vector<GLuint> textures;
    std::vector<GLenum> textureAttachments;
    std::vector<GLenum> textureFormatsInternal;
    std::vector<GLenum> textureFormats;
    std::vector<GLenum> textureType;

    std::vector<std::string> texturesName;
    GLuint depthTexture;

    unsigned int width; 
    unsigned int height;

};

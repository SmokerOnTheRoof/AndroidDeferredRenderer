#include "gbuffer.h"
#include "assert.h"

// only because to_string isn't working under android
#include <sstream>

#include <logging.h>

GBuffer::GBuffer()
    : framebuffer(0)
    , textures()
    , textureAttachments()
    , textureFormatsInternal()
    , textureFormats()
	, textureType()
	, texturesName()
	, depthTexture()
    , width(0)
    , height(0)

{

}

GBuffer::~GBuffer()
{
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(textures.size(), textures.data() );
    glDeleteTextures(1, &depthTexture);
}

void GBuffer::setSize( unsigned int newSize )
{
    textures.resize(newSize, 0);
    textureAttachments.resize(newSize);
    textureFormatsInternal.resize(newSize, GL_RGBA8UI);
    textureType.resize(newSize, GL_UNSIGNED_BYTE);
    textureFormats.resize(newSize, GL_RGBA);

    for(size_t i = 0; i < textureAttachments.size(); i++){
        textureAttachments.at(i) = GL_COLOR_ATTACHMENT0 + i;
        std::stringstream ss;
        ss << "Layer" << i << std::endl;
        texturesName.at(i) = ss.str();
    }

}

unsigned int GBuffer::getSize()
{
    return textures.size();
}

bool GBuffer::init()
{
    assert(textures.size() > 0);
    assert(width > 0);
    assert(height > 0);
    assert( 0 == framebuffer);

    GLint res;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &res);
	assert(textures.size() <= res);

    // Create the FBO
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

    // Create the gbuffer textures
    glGenTextures(textures.size(), textures.data() );
    glGenTextures(1, &depthTexture);

    for (unsigned int i = 0 ; i < textures.size() ; i++) {
        glBindTexture(GL_TEXTURE_2D, textures.at(i));
        glTexImage2D(GL_TEXTURE_2D, 0, textureFormatsInternal.at(i), width, height, 0, textureFormats.at(i), textureType.at(i), NULL);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textures.at(i), 0);
        GLenum error = glGetError();
        if(GL_INVALID_OPERATION == error){
            std::cout << "Error attaching Texture " << textures.at(i)<< " " << texturesName.at(i) << " to framebuffer." << std::endl;
            std::cout << "With format " << textureFormats.at(i) << " internal format " << textureFormatsInternal.at(i)
                      << " and type " << textureType.at(i) << " ." << std::endl;
        }
    }

    // depth
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
 
    glDrawBuffers(textureAttachments.size(), textureAttachments.data());

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FB error, status: " << Status << std::endl;
        return false;
    }

    // restore default FBO
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    return true;
}

void GBuffer::bindForWriting()
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
}

void GBuffer::bindForReading()
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
}

void GBuffer::setReadBuffer( unsigned int buffer )
{
    assert(buffer < textures.size());
    if(buffer < textures.size()){
        glReadBuffer(GL_COLOR_ATTACHMENT0 + buffer);
    }
}

void GBuffer::bindForLightPass()
{
    // Bind default framebuffer
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    for (unsigned int i = 0 ; i < textures.size() ; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures.at(i) );
    }
    glActiveTexture(GL_TEXTURE0 + textures.size());
    glBindTexture(GL_TEXTURE_2D, depthTexture );
}

void GBuffer::setLayer(size_t index, GLenum format, GLenum formatInternal, GLenum type, std::string name )
{
    textureFormats.at(index) = format;
    textureFormatsInternal.at(index) = formatInternal;
    textureType.at(index) = type;
    texturesName.at(index) = name;
}

void GBuffer::addLayer( GLenum format, GLenum formatInternal, GLenum type, std::string name )
{
    textures.push_back(0);
    textureAttachments.push_back(GL_COLOR_ATTACHMENT0 + textures.size()-1);
    textureFormatsInternal.push_back(formatInternal);
    textureType.push_back(type);
    textureFormats.push_back(format);
    texturesName.push_back(name);
}

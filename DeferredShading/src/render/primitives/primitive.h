#pragma once

#ifdef WIN32

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/GL.h>

#endif //WIN32

#ifdef ANDROID

#include <GLES3/GL3.h>
#include <GLES3/gl3ext.h>

#endif // ANDROID

#include <glm/glm.hpp>

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace Render{

/** \class Primitive
 *  \brief Base for all render primitives.
 *
 *  This class represents the base class for all render primitives.
 *  All render primitives at least contain a vertex array and
 *  a function for rendering.
 *
 */

class Primitive {

public:

    Primitive()
        : vertexArrayID(0)
        , vertexBufferID(0)
    {
        // Generate the vertex array and the vertex Buffer
        glGenVertexArrays(1, &vertexArrayID);
        glGenBuffers(1, &vertexBufferID);
    };

    virtual ~Primitive()
    {
        // Free the vertex array and the vertex Buffer
        glDeleteBuffers(1, &vertexBufferID);
        glDeleteVertexArrays(1, &vertexArrayID);
    };

    virtual void render() const = 0;

    /**
     *	\brief Returns the vertex array id of this primitive.
     *
     *  /return The vertex array id.
     */
    GLuint getVertexArrayID() const {return vertexArrayID;}

    /**
     *	\brief Return the vertex buffer id.
     *
     *	The vertex data stored at this id represents the locations
     *  of the vertices in object space.
     *
     *  /return returnValue
     */
    GLuint getVertexBufferID() const {return vertexBufferID;}

private:

    // The vertex array of this primitive
    GLuint vertexArrayID;

    // The vertex Buffer of this primitive
    GLuint vertexBufferID;

};

} // End namespace Render

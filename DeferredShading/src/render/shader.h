#pragma once

#include "plattformopengl.h"

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <map>

namespace Render {

/** Defines the shader type of the shader file which
 *  should be compiled.
 */

enum ShaderType {
    VERTEX = GL_VERTEX_SHADER, 
    FRAGMENT = GL_FRAGMENT_SHADER
};

/** \class Shader
 *  \brief Wrapper for GLSL shader.
 *
 *  The shader class allows easy compilation and linking of
 *  shader sources, shader binding an setting of uniforms.
 *
 *  First the shader must be compiled and linked. Before changing
 *  the uniform values. The shader must be bound.
 *
 */

class Shader {

public:

    Shader();
    ~Shader();

    // ToDo: Change return type of the compileShader functions to void
    //       and replace the current error handling with exceptions.
    //       Also it might be worth to wait till boost is compiled for
    //       Android to use the boost exceptions.

    /**
     *	\brief Compiles a shader from a std::stringstream.
     *
     *	Compiles a shader with the given type from a std::stringstream object.
     *
     *	/param stream   Const ref to the stringstream object.
     *	/param type     Type of the shader source.
     *  /return True if shader was successfully compiled, false otherwise.
     */
    bool compileShader(const std::stringstream& stream, ShaderType type);

    /**
     *	\brief Link the compiled shaders.
     *
     *  /return True if linking was successful, false otherwise.
     */
    bool link();

    /**
     *	\brief Bind the shader.
     *
     *  /return returnValue
     */
    void use() const;

    /**
     *	\brief Returns if the shader was successfully linked.
     *
     *  /return True if the shader was linked, false otherwise.
     */
    bool isLinked() const {return linked;};

    // ToDo: This one should be used from the primitives

    /**
     *	\brief Binds an attribute location to the given attribute index.
     *
     *	/param index    Index of the vertex attribute array.
     *	/param name     Name of the location.
     */
    void bindAttribLocation( GLuint index, const char * name);

    // ToDo: This value should come from the GBuffer.

    /**
     *	\brief Binds the output color to the specified buffer index.
     *
     *	/param index    Index of the output buffer.
     *	/param name     Name of the output location.
     */
    // void bindFragDataLocation( GLuint index, const char * name );
    
    /**
     *	\brief Sets the value of the vec2 with the specified name.
     *
     *	/param name Name of the vec2.
     *	/param v    Value of the vec2.
     */
    void setUniform(const char* name, const glm::vec2& v);
    
    /**
     *	\brief Sets the value of the vec3 with the specified name.
     *
     *	/param name Name of the vec3.
     *	/param v    Value of the vec3.
     */
    void setUniform(const char* name, const glm::vec3& v);
        
    /**
     *	\brief Sets the value of the vec4 with the specified name.
     *
     *	/param name Name of the vec4.
     *	/param v    Value of the vec4.
     */
    void setUniform(const char* name, const glm::vec4& v);
        
    /**
     *	\brief Sets the value of the mat4 with the specified name.
     *
     *	/param name Name of the mat4.
     *	/param m    Value of the mat4.
     */
    void setUniform(const char* name, const glm::mat4& m);
    
    /**
     *	\brief Sets the value of the mat3 with the specified name.
     *
     *	/param name Name of the mat3.
     *	/param m    Value of the mat3.
     */
    void setUniform(const char* name, const glm::mat3& m);

    /**
     *	\brief Sets the value of the float with the given name.
     *
     *	/param name Name of the float.
     *	/param val  Value of the float.
     */
    void setUniform(const char* name, float val );
    
    /**
     *	\brief Sets the value of the integer with the given name.
     *
     *	/param name Name of the integer.
     *	/param val  Value of the integer.
     */
    void setUniform(const char* name, GLint val );
        
    /**
     *	\brief Sets the value of the unsigned integer with the given name.
     *
     *	/param name Name of the unsigned integer.
     *	/param val  Value of the unsigned integer.
     */
    void setUniform(const char* name, GLuint val );
            
    /**
     *	\brief Sets the value of the boolean with the given name.
     *
     *	/param name Name of the boolean.
     *	/param val  Value of the boolean.
     */
    void setUniform(const char* name, GLboolean val );

private:

    GLuint programID;

    bool linked;

    std::map<std::string, int> uniformLocations;

    GLint getUniformLocation(const char* name);

    bool createProgram();

    static const char* getTypeString( GLenum type );

};

} // End namespace Render

#include "shader.h"

#include <algorithm>    // std::max

#include <vector>
#include <assert.h>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include <logging.h>

namespace Render{

Shader::Shader()
    : programID(0)
    , linked(false)
{

}

Shader::~Shader()
{
    if(programID >= 0){
        glDeleteProgram(programID);
    }
}

bool Shader::compileShader( const std::stringstream& stream, ShaderType type )
{
    // ToDo: Some sanity checking here

    if(!createProgram()){
        // ToDo: Error handling
    }

    GLuint shaderID = glCreateShader(type);

    std::string string = stream.str();
    char const * sourcePointer = string.c_str();
    GLint iShaderLen = stream.str().size();
    glShaderSource(shaderID, 1, &sourcePointer, &iShaderLen );

    glCompileShader(shaderID);

    // Check Vertex Shader
    GLint result = GL_FALSE;
    
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if(GL_FALSE == result){
        int infoLogLength;

        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

        std::vector<char> vertexShaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, vertexShaderErrorMessage.data());
        LOG(ERROR) << vertexShaderErrorMessage.data();

        glDeleteShader(shaderID);

        return false;
    }
    
    // Attach the shader to the program
    glAttachShader(programID, shaderID);
    
    glDeleteShader(shaderID); // ToDo: Does that work?

    return true;
}

bool Shader::link()
{ 
    //std::cout << "Linking program" << std::endl;

    glLinkProgram(programID);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    if( GL_FALSE == result ){
        int infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programErrorMessage( std::max( infoLogLength, int(1) ) );
        glGetProgramInfoLog(programID, infoLogLength, nullptr, programErrorMessage.data());
        LOG(ERROR) << "Linking of program failed: " << &programErrorMessage[0];
//#ifdef ANDROID
//        __android_log_print(ANDROID_LOG_ERROR, "OpenGLTestApp", "Linking of program failed: %s",  &programErrorMessage[0]);
//#endif
        return false;
    }
    linked = true;
    return true;
}

void Shader::use() const
{
    // ToDo: Check somehow if the shader is already set
    if(isLinked()){
        glUseProgram(programID);
    }
}

void Shader::bindAttribLocation( GLuint location, const char * name )
{
    glBindAttribLocation(programID, location, name);
}

void Shader::setUniform( const char* name, const glm::vec2& v )
{
    // ToDo: Check if the program is in use
    GLint loc = getUniformLocation(name);
    glUniform2fv(loc, 1, glm::value_ptr(v));
}

void Shader::setUniform( const char* name, const glm::vec3& v )
{
    GLint loc = getUniformLocation(name);
    glUniform3fv(loc, 1, glm::value_ptr(v));
}

void Shader::setUniform( const char* name, const glm::vec4& v )
{
    GLint loc = getUniformLocation(name);
    glUniform4fv(loc, 1, glm::value_ptr(v));
}

void Shader::setUniform( const char* name, const glm::mat4& m )
{
    GLint loc = getUniformLocation(name);
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setUniform( const char* name, const glm::mat3& m )
{
    GLint loc = getUniformLocation(name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::setUniform( const char* name, float val )
{
    GLint loc = getUniformLocation(name);
    glUniform1f(loc, val);
}

void Shader::setUniform( const char* name, GLint val )
{
    GLint loc = getUniformLocation(name);
    glUniform1i(loc, val);
}

void Shader::setUniform( const char* name, GLuint val )
{
    GLint loc = getUniformLocation(name);
    glUniform1ui(loc, val);
}

void Shader::setUniform( const char* name, GLboolean val )
{
    int loc = getUniformLocation(name);
    glUniform1i(loc, val);
}

GLint Shader::getUniformLocation( const char* name )
{
    std::map<std::string, int>::iterator pos;
    pos = uniformLocations.find(name);

    if( pos == uniformLocations.end() ) {
        uniformLocations[name] = glGetUniformLocation(programID, name);
    }

    return uniformLocations[name];
}

bool Shader::createProgram()
{
    if(programID <= 0){
        programID = glCreateProgram();
    }
    if(programID <= 0 ){
        // ToDo: Error
        return false;
    }
    return true;
}

} // End namespace Render


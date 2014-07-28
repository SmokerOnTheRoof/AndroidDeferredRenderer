#include "cube.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Render{

static const GLfloat cube_vertex_buffer_data[] = {
    // Front
    -0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    
     0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,

    // Left
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    
    // Right
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

    // Bottom
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    // Top
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
 
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,

    // Back

    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f
};

static const GLfloat cube_normal_buffer_data[] = {
    // Front
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,

    0, 0, 1,
    0, 0, 1,
    0, 0, 1,


    // Left
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,

    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,

    // Right
    1,0,0,
    1,0,0,
    1,0,0,

    1,0,0,
    1,0,0,
    1,0,0,

    // Bottom
    0,-1,0,
    0,-1,0,
    0,-1,0,

    0,-1,0,
    0,-1,0,
    0,-1,0,

    // Top
    0,1,0,
    0,1,0,
    0,1,0,


    0,1,0,
    0,1,0,
    0,1,0,

    // Back
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,

    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
};

Cube::Cube()
    : normalBufferID(0)
{
    glBindVertexArray(getVertexArrayID());

    // bind the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, getVertexBufferID());

    // Fill the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // ToDo: The index should be determined from the current shader
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    glEnableVertexAttribArray(0);

    glGenBuffers(1, &normalBufferID);

    glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_normal_buffer_data), cube_normal_buffer_data, GL_STATIC_DRAW);

    glVertexAttribPointer(
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_TRUE,            // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &normalBufferID);
}

void Cube::render() const
{
    // Use our shader

    glBindVertexArray(getVertexArrayID());

    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0, 3*12);

    glBindVertexArray(0);
}

} // End namespace Render

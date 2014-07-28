#include "quad.h"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Render{

static const GLfloat quad_vertex_buffer_data[] = { 
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,

    1.0f,  1.0f,
    -1.0f,  1.0f,
    1.0f, -1.0f};

Quad::Quad()
{
    glBindVertexArray( getVertexArrayID() );

    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, getVertexBufferID());

    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertex_buffer_data), quad_vertex_buffer_data, GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                  // ToDo: Get id from shader
        2,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Quad::~Quad()
{
    
}

void Quad::render() const
{
    // Use our shader
    glBindVertexArray( getVertexArrayID() );

    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0, 3*2); 

    glBindVertexArray(0);
}

} // End namespace Render

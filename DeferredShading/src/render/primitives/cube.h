#pragma once

#include "primitive.h"

namespace Render{

/** \class Cube
 *  \brief Render primitive of a Cube.
 *
 *  This class represents the primitive of a unit cube,
 *  with center at (0,0,0).
 *  The cube comes with a normal buffer.
 *
 */

class Cube : public Primitive{

public:

    Cube();
    ~Cube();

    /**
     *	\brief Reimplemented from Render::Primitive.
     *
     *  /return returnValue
     */
    virtual void render() const;

private:

    GLuint normalBufferID;

};

} // End namespace Render

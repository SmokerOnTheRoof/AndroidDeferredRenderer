#pragma once

#include "primitive.h"

namespace Render{

/** \class Quad
 *  \brief A quad render primitive.
 *
 *  A render primitive for a quad.
 *  It doesn't contain a normal map, because
 *  we use quads only for diffuse lights.
 *
 */

class Quad : public Primitive{

public:

    Quad();
    ~Quad();

    /**
     *	\brief Reimplemented from Render::Primitive
     *
     *  /return returnValue
     */
    virtual void render() const;

private:

};

} // End namespace Render
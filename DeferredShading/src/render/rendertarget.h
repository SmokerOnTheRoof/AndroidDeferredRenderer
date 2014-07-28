#pragma once

#include <glm/glm.hpp>

namespace Render{

/** \class RenderTarget
 *  \brief Interface for render targets.
 *
 *  This class represents an interface for render targets.
 *
 */

class RenderTarget{

public:

    /**
     *	\brief Returns the dimensions of the render target.
     *
     *	/return glm::uvec2 which contains the dimensions
     *			of the rendertarget.
     */
	virtual glm::uvec2 getDimensions() = 0;

};




}// End namespace Render

#pragma once

#include <memory>

#include "primitives/primitive.h"
#include "shader.h"

#include "camera.h"

namespace Render{

/** \class Light
 *  \brief Base class for all light sources.
 *
 *  Base class for all light sources.
 *
 */

class Light {

public:

    Light()
        : shader()
        , primitive()
        , screenSizeF(0.0f)
    {

    }
    ~Light(){}

    /**
     *	\brief Virtual method for updating the light parameters.
     *
     *	Every class which inherits from Light should implement this
     *  method.
     *
     */
    virtual void update(const Camera& camera) = 0;

    /**
     *	\brief Virtual method for rendering the light.
     *
     *	Every class which inherits from Light should implement this
     *  method.
     *
     */
    virtual void render() const = 0;

    /**
     *	\brief Sets the shader the light should use.
     *
     *	/param newShader Const shared pointer to the shader.
     */
    void setShader(const std::shared_ptr<Shader>& newShader){shader = newShader;}

    /**
     *	\brief Returns a const shared pointer to the shader this light source uses.
     *
     *  /return returnValue Shared pointer to the shader.
     */
    const std::shared_ptr<Shader>& getShader() const {return shader;}

    /**
     *	\brief Returns a non const shared pointer to the shader this light source uses.
     *
     *  /return returnValue Non const pointer to the shader.
     */
    std::shared_ptr<Shader>& getShader() {return shader;}

    /**
     *	\brief Sets the screen size.
     *
     *	Sets the screen size of the render windows or to be more precise the
     *  GBuffer.
     *
     *	/param newScreenSize Screen size of the render window.
     */
    void setScreenSize(const glm::vec2& newScreenSize){screenSizeF = newScreenSize;};

    /**
     *	\brief Returns a const ref to the screen size.
     *
     *  /return Screen size.
     */
    const glm::vec2& getScreenSize() const {return screenSizeF;}

    /**
     *	\brief Sets the shape of the light source.
     *
     *	/param newPrimitive Primitive for rendering the light.
     */
    void setPrimitive(std::shared_ptr<Primitive>& newPrimitive){primitive = newPrimitive;}

    /**
     *	\brief Return const ref to the shared pointer of the used primitive.
     *
     *  /return returnValue const reference to the shared pointer of the primitive.
     */
    const std::shared_ptr<Primitive>& getPrimitive() const {return primitive;}

    /**
     *	\brief Returns non const ref to the shared pointer of the used primitive.
     *
     *  /return returnValue non const reference to the shared pointer of the primitive.
     */
    std::shared_ptr<Primitive>& getPrimitive() {return primitive;}


private:

    std::shared_ptr<Shader> shader;

    std::shared_ptr<Primitive> primitive;

    glm::vec2 screenSizeF;


};



}// End namespace Render
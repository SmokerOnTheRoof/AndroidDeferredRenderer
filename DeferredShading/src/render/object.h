#pragma once

#include <memory>

#include "material.h"
#include "primitives/primitive.h"

#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Render {

/** \class Object
 *  \brief Base render object.
 *
 *  The render is a combination of a Render::Primitives::Primitive
 *  and a Material.
 *  Additionally it has a position (translation), scale and rotation.
 *  From these parameters the local matrix can be calculated, which is
 *  needed for rendering.
 *
 */

class Object {

public:

    Object(Material& newMaterial, std::shared_ptr<Primitive> newPrimitive);
    ~Object();

    /**
     *	\brief Updates the objects parameters.
     *
     *	/param projectionMatrix Projection matrix to use.
     *	/param viewMatrix View matrix to use.
     *  /return returnValue
     */
    virtual void update(const Camera camera);

    /**
     *	\brief Render the object.
     *
     *  Update must be called first.
     *
     *  /return returnValue
     */
    virtual void render() const;

    /**
     *	\brief Returns the local transformation matrix of the object.
     *
     *  /return Const ref of the local transformation matrix.
     */
    const glm::mat4 & getMatrixLocal() const {return matrixLocal;}

    /**
     *	\brief Returns the material of the object.
     *
     *  /return Const ref of the material.
     */
    const Material& getMaterial() const {return material;}

    /**
     *	\brief Returns the material of the object.
     *
     *  /return Ref of the material.
     */
    Material& getMaterial() {return material;}

    /**
     *	\brief Returns the render primitive this object uses.
     *
     *  /return Shared pointer to the primitive of the object.
     */
    std::shared_ptr<Primitive>& getPrimitive(){return primitive;}

    /**
     *	\brief Sets the position of the object.
     *
     *	/param newPosition The new position of the object.
     */
    void setPosition(const glm::vec3& newPosition)
    {
        matrixTranslation = glm::translate(glm::mat4(1), newPosition);
    }

    /**
     *	\brief Translates the object by the given vector.
     *
     *	/param newTranslation The translation vector.
     */
    void translate(const glm::vec3& newTranslation)
    {
        matrixTranslation = glm::translate(matrixTranslation, newTranslation);
    }

    /**
     *	\brief Apply the given quaternion to rotate the object.
     *
     *	/param quatRotation the rotation to apply.
     */
    void rotate(const glm::quat& quatRotation)
    {
        rotation = quatRotation * rotation;
    }

private:

    Material material;

    std::shared_ptr<Primitive> primitive;

    // The local transformation contains (scale, rotation and translation)
    glm::mat4 matrixLocal;

    // The translation
    glm::mat4 matrixTranslation;

    // The rotation (in fact its the current orientation)
    glm::quat rotation;

    // The scale
    glm::mat4 matrixScale;

};

} // End namespace Render
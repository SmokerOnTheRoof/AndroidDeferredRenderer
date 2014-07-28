#pragma once

#include <glm/glm.hpp>

#include "rendertarget.h"

namespace Render{

/** \class Camera
 *  \brief This class represents a simple Camera.
 *
 *  This class represents a Camera. It's just for calculation of
 *  the view and projection matrices.
 *  
 *  For future versions camera should be a subclass of Render::Object
 *  so basic movement can be applied. Also maybe this class should
 *  inherit from RenderTarget (which isn't implemented nor needed yet).
 *
 */

class Camera {

public:

    Camera();
    ~Camera();

    /**
     *  \brief Sets the render target
     *
     *  Sets the render target. Ownership remains at caller.
     *
     *  /param target The render target.
     */

    void setTarget(RenderTarget& target){renderTarget = &target;}

    /**
     *	\brief Sets the position of the camera.
     *
     *	/param position The new position.
     */
    void setPosition(const glm::vec3& position){eyePosition = position;}

    /**
     *	\brief Sets the view center.
     *
     *	/param center The center.
     */
    void setCenter(const glm::vec3& center){centerPosition = center;}

    /**
     *	\brief Sets the up vector of the camera.
     *
     *	/param up The up vector.
     */
    void setUp(const glm::vec3& up){upVector = up;}

    /**
     *	\brief Updates the view and projection matrices.
     */
    void update();

    /**
     *	\brief Get the view matrix.
     *
     *  /return The view matrix.
     */
    const glm::mat4& getViewMatrix() const {return viewMatrix;}

    /**
     *	\brief Get the projection matrix.
     *
     *  Call update first.
     *
     *  /return The projection matrix.
     */
    const glm::mat4& getProjectionMatrix() const {return projectionMatrix;}

    /**
     *	\brief Get the inverse of the projection matrix.
     *
     *  /return The inverse of the projection matrix.
     */
    const glm::mat4& getProjectionMatrixInv() const {return projectionMatrixInv;}

    /**
     *	\brief Returns the inverse of the view matrix.
     *
     *  /return The inverse of the view matrix.
     */
    const glm::mat4& getViewMatrixInv() const {return viewMatrixInv;}


    /**
     *	\brief Get the far clipping plane.
     *
     *  /return The location of the far clipping plane.
     */
    float getFarZ() const {return farClippingPlane;}

    /**
     *	\brief Get the far clipping plane.
     *
     *  /return The location of the far clipping plane.
     */
    float getNearZ() const {return nearClipingPlane;}

private:

    RenderTarget* renderTarget;

    glm::vec3 eyePosition;

    glm::vec3 centerPosition;

    glm::vec3 upVector;

    float fieldOfView; // FOV in Degree

    float aspectRatio;

    float nearClipingPlane;

    float farClippingPlane;

    glm::mat4 viewMatrix;

    glm::mat4 viewMatrixInv;

    glm::mat4 projectionMatrix;

    glm::mat4 projectionMatrixInv;

};



}// End namespace Render

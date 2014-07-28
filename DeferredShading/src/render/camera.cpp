#include "camera.h"

#include <assert.h>

#define GLM_FORCE_RADIANS

#include <glm/gtc/matrix_transform.hpp>

namespace Render{

Camera::Camera()
    : renderTarget(nullptr)
    , eyePosition(0,0,-5)
    , centerPosition(0)
    , upVector(0,1,0)
    , fieldOfView(45)
    , aspectRatio(16.0f/9.0f)
    , nearClipingPlane(0.1f)
    , farClippingPlane(100.0f)
    , viewMatrix(1)
	, viewMatrixInv(1)
    , projectionMatrix(1)
    , projectionMatrixInv(1)
{

}

Camera::~Camera()
{

}

void Camera::update()
{
	assert(nullptr != renderTarget);

	aspectRatio = (float)renderTarget->getDimensions().x / (float)renderTarget->getDimensions().y;

    viewMatrix = glm::lookAt( eyePosition, centerPosition, upVector);

    projectionMatrix = glm::perspective(    glm::radians(fieldOfView), 
                                            aspectRatio,
                                            nearClipingPlane,
                                            farClippingPlane);

    projectionMatrixInv = glm::inverse(projectionMatrix);

    viewMatrixInv = glm::inverse(viewMatrix);

}



}

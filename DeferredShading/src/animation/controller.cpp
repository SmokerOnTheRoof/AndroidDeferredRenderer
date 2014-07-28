#include "controller.h"

#include <render/object.h>

namespace Animation{

Controller::Controller()
    : object()
    , rotationQuat()
    , translation(0)
{

}

Controller::~Controller()
{

}

bool Controller::update(unsigned int stepSize)
{
    float stepFactor = stepSize / 1000.f;

    // Scale rotation and direction according to the step size
    glm::quat rotation = glm::mix(glm::quat(), rotationQuat, stepFactor);

    glm::vec3 dir = translation * stepFactor;

    auto shared_ptr = object.lock();

    if(shared_ptr){
        shared_ptr->rotate(rotation);
        shared_ptr->translate(dir);
    } else{
        return false;
    }
    return true;
}

void Controller::setRotation( const glm::vec3& axis, float rotation )
{
    glm::vec3 axisNormal = glm::normalize(axis);
    rotationQuat = glm::angleAxis( glm::radians(rotation),  axisNormal);
}

} // End namespace Animation

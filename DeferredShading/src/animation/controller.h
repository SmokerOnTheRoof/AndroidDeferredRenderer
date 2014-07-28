#pragma once

#include <memory>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Render{
    class Object;
}

#include "controller.h"

namespace Animation{

/** \class Controller
 *  \brief A simple movement controller.
 *
 *  This class represents a simple motion controller for
 *  Render::Objects. To use this class use the method setObject(),
 *  to set the object under control, set the desired motion, in which
 *  a object will move every second. Finally add the object to the 
 *  Animation::Manager which will schedule the updates every frame.
 *
 *  The controller will not take ownership for the object under control.
 *  It simply stores a std::weak_ptr to the object under control.
 *  However it's the callers responsibility to destroy the class if the
 *  object under control doesn't exist anymore.
 *
 *  For future versions different motion controller may be possible,
 *  i.e. a controller which applies motion based on user input, or
 *  more complex motion controllers.
 *
 */

class Controller{

public:

    Controller();
    ~Controller();

    /**
     *	\brief Sets the object which should be controlled.
     *
     *  Sets the object under control. Will take ownership over the object
     *  as a std::weak_ptr.
     *
     *	/param newObject    Shared pointer of the object.
     */
    void setObject(std::shared_ptr<Render::Object> newObject){object = newObject;}

    /**
     *	\brief Sets the Rotation.
     *
     *	Sets the rotation which should be applied to the object under control
     *  every second. The angle of the rotation is in degree.
     *
     *	/param axis     The rotation axis
     *	/param rotation Rotation in degree
     */
    void setRotation(const glm::vec3& axis, float rotation);

    /**
     *	\brief Sets the translation.
     *
     *	Sets the translation which should be applied every second.
     *
     *	/param trans  The translation.
     */
    void setTranslation(const glm::vec3& trans){translation = trans;}

    /**
     *	\brief Updates the object under control.
     *
     *	Updates the object under control to the state after the 
     *  specified milliseconds. Returns false if the object under control
     *  doesn't exist anymore, true otherwise.
     *
     *	/param milliseconds step size in milliseconds
     *  /return False if the object under control doesn't exist anymore, true otherwise.
     */
    bool update(unsigned int milliseconds);

private:

    std::weak_ptr<Render::Object> object;

    glm::quat rotationQuat;

    glm::vec3 translation;



};

}

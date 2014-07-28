#pragma once

#include "light.h"

namespace Render{

/** \class DirectionalLight
 *  \brief A directional light source.
 *
 *  This class represents a directional light source.
 *  Because we do deferred shading every light source needs
 *  the screen size of the render target, to get all geometrical 
 *  informations.
 *
 */

class DirectionalLight : public Light{

public:

    DirectionalLight();
    ~DirectionalLight();

    /**
     *	\brief Sets the direction of the light.
     *
     *	/param dir  The direction.
     */
    void setDirection(const glm::vec3& dir)
    {
     direction = glm::normalize(dir);   
    }

    /**
     *	\brief Reimplemented from Render::Light.
     *
     */
    virtual void update(const Camera& camera);

    /**
     *	\brief Reimplemented from Render::Light.
     *
     */
    virtual void render() const;

private:

    glm::vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    glm::vec3 direction;
    float specularIntensity;
    float specularPower;

};


}// End namespace Render
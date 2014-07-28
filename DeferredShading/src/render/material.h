#pragma once

#include "shader.h"

#include <memory>

#include "glm/glm.hpp"

namespace Render {

/** \class Material
 *  \brief Base Material.
 *
 *  This class represents the base for all Materials.
 *  A Material is a combination from a Render::Shader
 *  and additional components such as diffuse color
 *  and shininess.
 *
 *  The Base Material represents a Material where all
 *  components affect the whole object. Except for Normals
 *  which are per vertex face pair.
 *
 *  For future development additional Materials should be possible,
 *  which allow material parameters from textures as well.
 *
 */

class Material {

public:

    Material( std::shared_ptr<Shader>& newShader);
    ~Material();

    /**
     *	\brief Sets the diffuse color of the material.
     *
     *	/param color The new material diffuse color.
     */
    void setDiffuseColor(const glm::vec3& color){diffuseColor = color;}

    /**
     *	\brief Sets the shininess of the material.
     *
     *	/param factor   The shininess factor.
     */
    void setShininess(GLfloat factor){shininess = factor;}

    /**
     *	\brief Bind the material.
     *
     */
    void use() const;

    /**
     *	\brief Updates the material parameters.
     *
     */
    void update();

    /**
     *	\brief Returns reference to the shared pointer to the material shader.
     *
     */
    std::shared_ptr<Shader>& getShader(){return shader;}

private:

    std::shared_ptr<Shader> shader;

    glm::vec3 diffuseColor;

    GLfloat shininess;

};

} // End namespace Render
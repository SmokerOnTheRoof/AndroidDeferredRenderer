#include "material.h"

namespace Render {

    Material::Material( std::shared_ptr<Shader>& newShader )
        : shader(newShader)
        , diffuseColor(0.5f)
        , shininess(1.0f)
    {

    }

    Material::~Material()
    {

    }

    void Material::use() const
    {
        shader->use();
    }

    void Material::update()
    {
        getShader()->use();

        getShader()->setUniform("color", diffuseColor);

        // ToDo: set specularColor
        // ToDo: set shininess

    }

} // End namespace Render
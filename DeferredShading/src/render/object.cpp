#include "object.h"

namespace Render {

Object::Object( Material& newMaterial, std::shared_ptr<Primitive> newPrimitive )
    : material(newMaterial)
    , primitive(newPrimitive)
    , matrixLocal(1)
    , matrixTranslation(1)
    , rotation()
    , matrixScale(1)
{

}

Object::~Object()
{

}

void Object::update(const Camera camera)
{
    getMaterial().use();

    getMaterial().update();

    glm::mat4 matrixRotation = glm::mat4_cast( rotation );

    matrixLocal = matrixScale * matrixRotation * matrixTranslation;

    glm::mat4 matrixMVP = camera.getProjectionMatrix() * camera.getViewMatrix() * matrixLocal;

    getMaterial().getShader()->setUniform("MVP", matrixMVP);

    getMaterial().getShader()->setUniform("M", matrixLocal);

    getMaterial().getShader()->setUniform("V", camera.getViewMatrix());

}

void Object::render() const
{
    getMaterial().use();
    primitive->render();
}

} // End namespace Render
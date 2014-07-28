#include "directionallight.h"

#include "primitives/quad.h"

#include <assert.h>

namespace Render{

DirectionalLight::DirectionalLight()
    : color(1.0f, 1.0f, 1.0f)
    , ambientIntensity(0.05f)
    , diffuseIntensity(0.5f)
    , direction(0.0f, -1.0f, 0.0f)
    , specularIntensity(1.0f)
    , specularPower(1.0f)
{
    // ToDo: Let some other class handle the setting of the primitive
    std::shared_ptr<Primitive> primitive = std::make_shared<Quad>();

    setPrimitive(primitive);
}

DirectionalLight::~DirectionalLight()
{

}

void DirectionalLight::update(const Camera& camera)
{
    assert(glm::vec2(0) != getScreenSize() );

    getShader()->use();

    getShader()->setUniform("directionalLight.color", color);

    getShader()->setUniform("directionalLight.direction", direction);

    getShader()->setUniform("directionalLight.ambientIntensity", ambientIntensity);

    getShader()->setUniform("directionalLight.diffuseIntensity", diffuseIntensity);

    getShader()->setUniform("specularIntensity", specularIntensity);

    getShader()->setUniform("specularPower", specularPower);

    getShader()->setUniform("screenSize", getScreenSize() ); // ToDo: Move to camera

    getShader()->setUniform("V", camera.getViewMatrix());

    getShader()->setUniform("invP", camera.getProjectionMatrixInv());

    float zFar = camera.getFarZ();
    float zNear = camera.getNearZ();

    float projectionA = -(zFar+zNear) / ( zFar - zNear);
    float projectionB = (-2*zFar * zNear) / (zFar - zNear);

    getShader()->setUniform("projectionA", projectionA);
    getShader()->setUniform("projectionB", projectionB);

    //getShader()->setUniform("invView", camera.getViewMatrixInv());

    // ToDo: These values should be read from the gbuffer
    //        Maybe each update should contain a render target.
    //        In this case it would be a camera attached to a gbuffer.
    //        Just thinking loudly.

    getShader()->setUniform("colorMap", 0);
    getShader()->setUniform("normalVSMap", 1);
    getShader()->setUniform("depthMap", 2);

}

void DirectionalLight::render() const
{
   getShader()->use();

   getPrimitive()->render();
}



}// End namespace Render

#include "application.h"

#include <render/shader.h>
#include <render/material.h>
#include <render/object.h>
#include <render/primitives/cube.h>
#include <render/camera.h>
#include <render/directionallight.h>
#include <animation/controller.h>

Application::Application()
	: contRendering(true)
	, screenSize(0, 0)
	, renderer(glm::vec2(0, 0))
	, assetManager()
{

}

Application::Application(unsigned int newWidth, unsigned int newHeight)
    : contRendering(true)
    , screenSize(newWidth, newHeight)
    , renderer(glm::vec2(newWidth, newHeight))
	, assetManager()
{
    
}

Application::~Application()
{

}


int Application::exec()
{
    while(contRendering){

        handleEvents();

        if(needsUpdate()){

        	unsigned int duration = timer.getDuration();

        	animationManager.update(duration);

        	renderer.render();

        	postRender();
        }
    }
    return 0;
}

void Application::createObjects()
{

    auto shader = getAssetManager().loadShader("geometry.vert", "geometry.frag");

    shader->link();

    Render::Material material1(shader);
    material1.setDiffuseColor(glm::vec3(1.0f, 0.0f, 0.0f));
    Render::Material material2(shader);
    material2.setDiffuseColor(glm::vec3(0.0f, 1.0f, 0.0f));
    Render::Material material3(shader);
    material3.setDiffuseColor(glm::vec3(0.0f, 0.0f, 1.0f));
    Render::Material material4(shader);
    material4.setDiffuseColor(glm::vec3(0.5f, 0.5f, 0.5f));

    std::shared_ptr<Render::Cube> cubePrimitive = std::make_shared<Render::Cube>();

    std::shared_ptr<Render::Object> cube1 = std::make_shared<Render::Object>(material1 , cubePrimitive);
    std::shared_ptr<Render::Object> cube2 = std::make_shared<Render::Object>(material2 , cubePrimitive);
    std::shared_ptr<Render::Object> cube3 = std::make_shared<Render::Object>(material3 , cubePrimitive);
    std::shared_ptr<Render::Object> cube4 = std::make_shared<Render::Object>(material4 , cubePrimitive);

    getRenderer().addObject(cube1);
    getRenderer().addObject(cube2);
    getRenderer().addObject(cube3);
    getRenderer().addObject(cube4);

    cube1->translate(glm::vec3(  0.0f,  1.0f, 0.0f ) );
    cube2->translate(glm::vec3( -1.5f,  0.0f, 0.0f ) );
    cube3->translate(glm::vec3(  0.0f, -1.0f, 0.0f ) );
    cube4->translate(glm::vec3(  1.5f,  0.0f, 0.0f ) );

    std::shared_ptr<Render::Camera> camera( new Render::Camera);
    camera->setTarget(renderer);
    camera->setPosition(glm::vec3(0.0f, 0.0f, -5.0f));

    getRenderer().addCamera(camera);

    std::shared_ptr<Render::DirectionalLight> directionalLight( new Render::DirectionalLight );

    auto directionalLightShader = getAssetManager().loadShader("directionallight.vert", "directionallight.frag");
    directionalLight->setShader(directionalLightShader);

    directionalLight->setDirection(glm::vec3(-1.0f, -1.0f, -1.0f));

    getRenderer().addLight(directionalLight);

    Animation::Controller cube1Controller, cube2Controller, cube3Controller, cube4Controller;

    cube1Controller.setObject(cube1);
    cube1Controller.setRotation(glm::vec3(0.0f,1.0f,0.0f), 90.0f);
    cube2Controller.setObject(cube2);
    cube2Controller.setRotation(glm::vec3(1.0f,0.0f,0.0f), -90.0f);
    cube3Controller.setObject(cube3);
    cube3Controller.setRotation(glm::vec3(0.0f,-1.0f,0.0f), 90.0f);
    cube4Controller.setObject(cube4);
    cube4Controller.setRotation(glm::vec3(-1.0f,0.0f,0.0f), -90.0f);

    getAnimationManager().addController(cube1Controller);
    getAnimationManager().addController(cube2Controller);
    getAnimationManager().addController(cube3Controller);
    getAnimationManager().addController(cube4Controller);
}

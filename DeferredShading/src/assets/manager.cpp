#include "manager.h"

#include <assert.h>

namespace Assets{

Manager::Manager()
	: assetLoader(nullptr)
{

}

Manager::~Manager() {
    if(nullptr != assetLoader){
        delete assetLoader;
    }
}

void Manager::loadAsset(const char* filename, std::stringstream& stream) {
	assert(nullptr != assetLoader);

    assetLoader->loadAsset(filename, stream);
}

std::shared_ptr<Render::Shader> Manager::loadShader(const char* filenameVS, const char* filenameFS) {

	std::shared_ptr<Render::Shader> shader = std::make_shared<Render::Shader>();

	std::stringstream streamVs;

	loadAsset(filenameVS, streamVs);

	shader->compileShader(streamVs , Render::VERTEX);

	std::stringstream streamFs;

	loadAsset(filenameFS, streamFs);

	shader->compileShader(streamFs , Render::FRAGMENT);

	shader->link();

	return shader;
}

} // End namespace Assets


#include "loaderdesktop.h"

#include "logging.h"

namespace Assets{

LoaderDesktop::LoaderDesktop() 
{

}

LoaderDesktop::~LoaderDesktop() 
{

}

void LoaderDesktop::loadAsset(const char* filename, std::stringstream& stream) {

	std::ifstream shaderStream(filename, std::ios::in);
	if(shaderStream.is_open())
	{
		stream << shaderStream.rdbuf();
		shaderStream.close();
	} else{
		LOG(ERROR) << "Asset " << filename << " could not been opened.";
	}
}

}// End namespace Assetes

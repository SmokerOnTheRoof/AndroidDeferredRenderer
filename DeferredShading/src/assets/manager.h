#pragma once

#include <sstream>
#include <memory>

#include "loader.h"

#include <Render/shader.h>

namespace Assets{

/** \class Manager
 *  \brief An asset manager.
 *
 *  This class should be an asset loader, but it's not.
 *  Actually this is just a file loader which can generate shader files.
 *  If i ever touch this code again i will start here an implement an
 *  actual asset loader.
 */

//ToDo: Write actual asset manager.

class Manager{

public:

	Manager();
	~Manager();

    /**
     *	\brief Sets the loader which should be used for loading files.
     *
     *  This method sets the loader object which is responsible for
     *  actually loading files. The manager class will take ownership
     *  of the loader.
     *
     *	/param loader Pointer to instance of Loader.
     */

	void setAssetLoader(Loader* loader){assetLoader = loader;}

    /**
     *	\brief Sets the loader which should be used for loading files.
     *
     *  This methods generates a shader object from a vertex shader and fragment
     *  shader input file.
     *
     *	/param filenameVS Path to the vertex shader.
     *	/param filenameFS Path to the fragment sahder.
     *	/return Compiled and linked shader object encapsuled in a shared_ptr
     */

	std::shared_ptr<Render::Shader> loadShader(const char* filenameVS, const char* filenameFS);

private:

	void loadAsset(const char* filename, std::stringstream& stream);

	//Cache assetCache; // ToDo: Later

	Loader* assetLoader;

};

} // End namspace Assets

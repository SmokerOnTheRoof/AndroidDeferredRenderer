#pragma once

#include "loader.h"

#include <android/asset_manager.h>

namespace Assets{

/** \class LoaderAndroid
 *  \brief Asset loader for files in android apks.
 *
 *  The LoaderAndroid is an asset loader for apk files.
 */

class LoaderAndroid : public Loader{

public:

	LoaderAndroid(AAssetManager* aassetManager);
	virtual ~LoaderAndroid();

	/**
	 * Re-Implemented from Loader.
	 */
	virtual void loadAsset(const char* filename, std::stringstream& stream);

private:

	AAssetManager* assetManager;

};

}// End namespace Assets

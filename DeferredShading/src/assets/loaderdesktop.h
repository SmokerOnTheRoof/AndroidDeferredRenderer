#pragma once

#include "loader.h"

namespace Assets{

/** \class LoaderDesktop
 *  \brief Asset loader for filesystem files.
 *
 *  The LoaderAndroid is an asset loader for general file system files.
 *  The name is somehow confusing. Currently the android version loads all
 *  assets directly from the apk. The LoaderDesktop is used for the desktop
 *  versions.
 */

class LoaderDesktop : public Loader{

public:

	LoaderDesktop();
	virtual ~LoaderDesktop();

	/**
	 *	Re-Implemented from Loader.
	 */
	virtual void loadAsset(const char* filename, std::stringstream& stream);

private:

};

}// End namespace Assets

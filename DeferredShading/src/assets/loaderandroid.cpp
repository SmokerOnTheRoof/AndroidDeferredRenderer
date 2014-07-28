#include "loaderandroid.h"

#include <vector>
#include <memory>
#include <functional>

#include "logging.h"

#include <android/asset_manager.h>

namespace Assets{

LoaderAndroid::LoaderAndroid(AAssetManager* aassetManager)
	: Loader()
	, assetManager(aassetManager)

{
}

LoaderAndroid::~LoaderAndroid()
{

}

void LoaderAndroid::loadAsset(const char* filename, std::stringstream& stream) {

	//auto del = AAsset_close();
	std::unique_ptr<AAsset, void (*)(AAsset*)> asset(AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER), AAsset_close);
	//std::unique_ptr<AAsset> asset(AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER));
	//asset.get_deleter()

	//AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);

	if(asset){
		//std::string content;
		//content.resize(AAsset_getLength( asset ));
		std::vector<char> buffer;
		buffer.resize(AAsset_getLength( asset.get() ));
		//AAsset_read(asset, (void *)content.data(), content.size()); // ToDo: ugly hack
		AAsset_read( asset.get(), (void *)buffer.data(), buffer.size());
		//stream << content;
		stream.write(buffer.data(), buffer.size());
	} else{
		LOG(WARNING) << "Asset %s not found";
	}

	// ToDo: I want to return a stringstream object, but gnu_std doesn't support move constructor for stringstreams



}



}// End namespace Assets

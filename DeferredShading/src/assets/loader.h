#pragma once

#include <sstream>

namespace Assets{

/** \class Loader
 *  \brief Interface for Asset loaders.
 *
 *  This class represents an interface for asset loaders.
 *  Every AssetLoader has a method loadAsset(const char*, std::stringstream&)
 *  which loads a file with the specified name into a std::stringstream.
 *
 */

class Loader{

public:

    Loader(){};
    virtual ~Loader() {};

    /**
     *	\brief Loads a file to the given std::stringstream.
     *
     *  This method loads the file filename to the std::stringstream& stream.
     *
     *	/param filename path to the file.
     *	/param stream 	Output std::stringstream object.
     */
	virtual void loadAsset(const char* filename, std::stringstream& stream) = 0;

};

} // End namespace Assets

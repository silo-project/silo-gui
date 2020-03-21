#include "tinyxml2.h"
#include "LibraryManager.hpp"

namespace FileLoader {
	int LoadFile(const char*, LibraryManager*, int);
	RootPartbyRootPlane* LoadCircuit(const tinyxml2::XMLElement*, LibraryManager*);
	Library* LoadDefaultLibrary(const char*);
}
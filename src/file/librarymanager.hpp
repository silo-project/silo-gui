#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <map>
#include <string>
#include <cstdint>
#include "part.hpp"

namespace LibraryManager {
	int init();
	int regLibrary(const char*, uint32_t, PartManager);
	uint32_t findLibraryID(const char*);
	PartManager findPartManager(uint32_t);
	int loadLibrary(const char*);
	extern std::map<std::string, uint32_t> LibraryIDMap;
	extern std::map<uint32_t, PartManager> PartManagerMap;
}

#endif
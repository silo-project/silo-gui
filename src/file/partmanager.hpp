#ifndef PARTMANAGER_H
#define PARTMANAGER_H

#include <map>
#include <string>
#include <cstdint>
#include "part.hpp"

namespace PartManager {
	int init();
	int addPart(const char*, uint32_t, const char*);
	int addPart(const char*, uint32_t, uint32_t, const char*);
	_PartID findPartID(const char*);
	extern std::map<std::string, _PartID> partIDMap;
	extern std::map<_PartID, std::string> partSVGMap;
}

#endif
#ifndef PARTMANAGER_H
#define PARTMANAGER_H

#include <map>
#include <string>
#include <cstdint>
#include "part.hpp"

class PartManager {
public:
	int init();
	int regPart(const char*, uint32_t, const char*);
	_PartID findPartID(const char*);
protected:
	extern std::map<std::string, uint32_t> partIDMap;
}

#endif
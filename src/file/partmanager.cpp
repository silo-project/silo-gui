#include "partmanager.hpp"

#include <iostream>

std::map<std::string, _PartID> PartManager::partIDMap;
std::map<_PartID, std::string> PartManager::partSVGMap;

int PartManager::addPart(const char* name, uint32_t partid, const char* svg) { addPart(name, -1, partid, svg); }

int PartManager::addPart(const char* name, uint32_t libraryid, uint32_t partid, const char* svg) {
	std::string sname(name);
	_PartID pid = generatePartID(UINT32_MAX, partid);
	partIDMap[sname] = pid;
	std::string ssvg(svg);
	partSVGMap[pid] = svg;
}

_PartID PartManager::findPartID(const char* name) {
	std::string sname(name);
	std::cout << partIDMap.find(sname)->first << std::endl;
}
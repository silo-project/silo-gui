#include "partmanager.hpp"

#include <iostream>
#include <string>
#include <map>

using namespace std;

map<string, uint32_t> PartManager::partIDMap;

int PartManager::init() {
	return 0;
}

int PartManager::regPart(const char* name, uint32_t partid, const char* svg) {
	string sname(name);
	partIDMap[sname] = partid;
	//string ssvg(svg);
	//partSVGMap[pid] = ssvg;
	return 0;
}

_PartID PartManager::findPartID(const char* name) {
	string sname(name);
	int i = partIDMap[libraryid][sname];
	std::cout << i << std::endl;
	return i;
}
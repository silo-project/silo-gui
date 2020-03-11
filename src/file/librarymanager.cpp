#include "librarymanager.hpp"
#include "partmanager.hpp"

#include <iostream>
#include <string>
#include <cstring>
#include <map>

using namespace std;
using namespace LibraryManager;

int LibraryManager::init() {

}

int LibraryManager::regLibrary(const char* name, uint32_t libraryid, PartManager partManager) {
	string sname(name);
	LibraryIDMap.insert({ sname, libraryid });
	PartManagerMap.insert({ libraryid, partManager });
	return 0;
}

uint32_t LibraryManager::findLibraryID(const char* name) {
	String sname(name);
	return LibraryIDMap[sname];
}

PartManager* LibraryManager::findPartManager(uint32_t libraryid) {
	return PartManagerMap[libraryid];
}

std::map<std::string, uint32_t> LibraryManager::LibraryIDMap;
std::map<uint32_t, PartManager*> LibraryManager::PartManagerMap;

PartManager* LibraryManager::loadLibrary(const char* name) {
	PartManager* pm = new PartManager();
	if (strcmp(name, "#Wiring") == 0) {
		pm->regPart("Splitter", 0, "");
	} else if (strcmp(name, "#Gates") == 0) {
		pm->regPart("Splitter", 0, "");
	} else if (strcmp(name, "#Plexers") == 0) {

	} else if (strcmp(name, "#Arithmetic") == 0) {

	} else if (strcmp(name, "#Memory") == 0) {

	} else if (strcmp(name, "#I/O") == 0) {

	} else if (strcmp(name, "#Base") == 0) {

	}
}
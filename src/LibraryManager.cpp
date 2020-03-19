#include <map>
#include "LibraryManager.hpp"

auto LibraryManager::getInstance() {
	if (libraryMap == nullptr) libraryMap = new std::map<libraryID, Library*>();
	return libraryMap;
}
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <map>
#include <string>

#include "Library.hpp"

class LibraryManager {
public:
	std::map<std::string, libraryID> libraryNameMap;
	std::map<libraryID, Library*> libraryMap;
};

#endif
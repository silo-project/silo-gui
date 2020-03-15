#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <map>

#include "Library.hpp"

class LibraryManager {
public:
	extern std::map<libraryID, Library*> libraryMap;
};

#endif
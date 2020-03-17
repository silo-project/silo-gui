#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <map>

#include "Library.hpp"

namespace LibraryManager {
	std::map<libraryID, Library*> libraryMap;
};

#endif
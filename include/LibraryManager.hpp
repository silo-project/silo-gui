#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <vector>
#include <string>

#include "Library.hpp"

class LibraryManager {
public:
	std::vector<std::string> libraryNameVector;
	std::vector<Library*> libraryVector;
};

#endif
#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include <map>

#include "Library.hpp"

class LibraryManager {
protected:
	static std::map<libraryID, Library*>* libraryMap;
public:
	static auto getInstance();
};

#endif
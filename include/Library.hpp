#ifndef LIBRARY_H
#define LIBRARY_H

#include <cstdint>

#include "RootPart.hpp"

class Library {
public:
	std::map<rootPartID, RootPart*> rootPartMap;
};

#endif
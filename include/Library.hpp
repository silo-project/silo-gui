#ifndef LIBRARY_H
#define LIBRARY_H

#include <cstdint>

#include "RootPart.hpp"

class Library {
public:
	std::vector<RootPart*> rootPartVector;
};

#endif
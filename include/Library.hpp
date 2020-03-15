#ifndef LIBRARY_H
#define LIBRARY_H

#include <cstdint>

#include "Part.hpp"

#define ROOT_LIBRARY UINT32_MAX

typedef uint32_t libraryID;

class Library {
public:
	extern std::map<partID, Part*> partMap;
};

#endif
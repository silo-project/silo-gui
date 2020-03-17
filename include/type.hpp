#ifndef TYPE_H
#define TYPE_H

typedef int pinID;

typedef int pinWidth;

#include <vector>

typedef int DrawableObject;

typedef uint32_t partID;

typedef std::vector<DrawableObject> DrawableVector;

enum Side {
	NORTH = 1, SOUTH, EAST, WEST
};

typedef int wireID;

#endif
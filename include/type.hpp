#ifndef TYPE_H
#define TYPE_H

using pinID = int;

using pinWidth = int;

#include <vector>

using DrawableObject = int;

using partID = uint32_t;

using DrawableVector = std::vector<DrawableObject>;

enum Side {
	NORTH = 1, SOUTH, EAST, WEST
};

using planeID = uint32_t;
using xy = int32_t;

using wireID = int;

using libraryID = uint32_t;

using rootPartID = uint32_t;

#define ROOT_LIBRARY UINT32_MAX

#endif
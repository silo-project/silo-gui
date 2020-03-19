#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

#include "type.hpp"

struct Position {
	planeID p;
	xy x;
	xy y;
};

namespace PositionUtil {
	inline planeID getPlaneID(Position* pos) { return pos->p; }
	inline xy getX(Position* pos) { return pos->x; }
	inline xy getY(Position* pos) { return pos->y; }
}

#endif
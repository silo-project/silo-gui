#ifndef WIRE_H
#define WIRE_H

#include "Value.hpp"

enum WirePull {
	PULL_NO = 0,
	PULL_UP, PULL_DOWN
};

struct Wire {
	Value value;
	WirePull pullup;
};

struct WirePos {
	Position a, b;
};

#endif
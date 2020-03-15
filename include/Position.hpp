#ifndef POSITION_H
#define POSITION_H

#include <cstdint>

struct xy {
	int32_t x;
	int32_t y;
};

union Position {
	uint64_t value;
	xy xy;
};

#endif
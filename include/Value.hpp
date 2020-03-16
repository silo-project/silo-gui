#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

struct Value {
	uint8_t		width;
	uint64_t	value;
	uint64_t	state;
};

#endif
#ifndef PIN_H
#define PIN_H

#include "Position.hpp"
#include "Wire.hpp"

typedef int pinID;

typedef int pinWidth;

enum PinType { PIN_INPUT = 0, PIN_OUTPUT };

struct Pin {
	Position offset;
	PinType pinType;
	pinWidth width;
	Wire* connectedWire;
};

#endif
#ifndef CIRCUITPART_H
#define CIRCUITPART_H

#include <cstdint>
#include <map>
#include <string>

#include "Position.hpp"
#include "Part.hpp"
#include "Pin.hpp"

class CircuitPart {
private:
	Part* partPointer;
public:
	Position pos;
	std::map<std::string, std::string> options;
	std::map<pinID, Pin> pins;
	inline Part* getPartPointer() { return partPointer; }
	CircuitPart(Part* pp);
	~CircuitPart();
};

#endif
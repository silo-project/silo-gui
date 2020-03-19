#ifndef CIRCUITPART_H
#define CIRCUITPART_H

#include <cstdint>
#include <map>
#include <string>

#include "type.hpp"

#include "Position.hpp"
#include "Pin.hpp"

class RootPart;

class CircuitPart {
protected:
	RootPart* partPointer;
public:
	Position pos;
	std::map<std::string, std::string> options;
	std::map<pinID, Pin*> pins;
	inline RootPart* getPartPointer() { return partPointer; }
	CircuitPart(RootPart* pp);
	~CircuitPart();
};

struct CircuitPartonCircuitPlane : public Position {
	CircuitPart* c;
};

#endif
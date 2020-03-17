#ifndef CIRCUITPARTCIRCUIT_H
#define CIRCUITPARTCIRCUIT_H

#include <cstdint>
#include <map>
#include <string>

#include "type.hpp"

#include "PartCircuit.hpp"
#include "Position.hpp"
#include "Pin.hpp"

class Part;

class CircuitPartCircuit : public CircuitPart {
protected:
	PartCircuit* circuitPointer;
public:
	Position pos;
	std::map<std::string, std::string> options;
	std::map<pinID, Pin*> pins;
	inline PartCircuit* getCircuitPointer() { return circuitPointer; }
	CircuitPartCircuit(CircuitPartCircuit* pp);
	~CircuitPartCircuit();
};

#endif
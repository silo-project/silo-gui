#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "CircuitPart.hpp"
#include "Pin.hpp"
#include "Part.hpp"

#include "type.hpp"

class PartCircuit : public Part {
public:
	std::map<wireID, WirePos*> wires;
	class CircuitPartCircuit* GenerateCircuitPartCircuit(std::map<std::string, std::string>);
	DrawableVector* DrawCircuit(class CircuitPartCircuit*);
};

#endif
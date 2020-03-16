#ifndef PART_H
#define PART_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "CircuitPart.hpp"
#include "Pin.hpp"

#include "type.hpp"

class Part {
private:
	uint32_t LibraryID, PartID;
public:
	inline uint32_t getLibraryID() { return LibraryID; }
	inline uint32_t getPartID() { return PartID; }
	std::map<pinID, Pin*> pins;
	class CircuitPart* GenerateCircuitPart(std::map<std::string, std::string>);
	DrawableVector* DrawCircuit(class CircuitPart*);
};

#endif
#ifndef ROOTPART_H
#define ROOTPART_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "CircuitPart.hpp"
#include "Pin.hpp"
#include "Position.hpp"

#include "type.hpp"

class RootPart {
protected:
	uint32_t LibraryID, PartID;
public:
	inline uint32_t getLibraryID() { return LibraryID; }
	inline uint32_t getPartID() { return PartID; }
	std::map<pinID, Pin*> pins;
	CircuitPart* GenerateCircuitPart(std::map<std::string, std::string>);
	DrawableVector* DrawCircuit(class CircuitPart*);
};

struct RootPartonRootPlane : public Position {
	RootPart* r;
};

#endif
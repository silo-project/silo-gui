#ifndef PART_H
#define PART_H

#include <cstdint>
#include <map>
#include <vector>
#include <string>

#include "CircuitPart.hpp"

typedef int DrawbleObject; // TODO: Sth.

typedef uint32_t partID;

typedef std::vector<DrawableObject> DrawableVector;

class Part {
private:
	uint32_t LibraryID, PartID;
public:
	inline uint32_t getLibraryID() { return LibraryID; }
	inline uint32_t getPartID() { return PartID; }
	CircuitPart* GenerateCircuitPart(std::map<std::string, std::string>);
	virtual DrawableVector DrawCircuit(CircuitPart*);
};

#endif
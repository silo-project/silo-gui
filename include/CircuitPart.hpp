#ifndef CIRCUITPART_H
#define CIRCUITPART_H

#include <cstdint>
#include <map>
#include <string>

#include "Position.hpp"

class Part {
private:
	Part * partPointer;
	Position pos;
public:
	std::map<std::string, std::string> options;
	std::map<> pins;
	MAP<IO Pin ID, CLASS Pin>
};

#endif
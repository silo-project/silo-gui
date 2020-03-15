#ifndef CIRCREADER_H
#define CIRCREADER_H

#include "circuit.hpp"

#include <vector>

#include "tinyxml2.h"

namespace CircReader {
	int readFile(char*, std::vector<Circuit*>*);
	Circuit* readCirc(tinyxml2::XMLElement*, std::vector<Circuit*>*);
}
#endif
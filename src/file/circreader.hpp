#ifndef CIRCREADER_H
#define CIRCREADER_H

#include "circuit.hpp"

#include <set>

#include "../tinyxml2/tinyxml2.h"

namespace CircReader {
	int readFile(char*, std::set<Circuit*>*);
	Circuit* readCirc(tinyxml2::XMLElement*);
}
#endif
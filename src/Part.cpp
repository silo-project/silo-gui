#include <map>
#include <vector>
#include <string>

#include "Part.hpp"
#include "CircuitPart.hpp"

using namespace std;

CircuitPart* Part::GenerateCircuitPart(map<string, string> options) {
	CircuitPart* p = new CircuitPart(this);
	return p;
}
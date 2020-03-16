/*#ifdef _MSC_VER
#undef _CRT_SECURE_DEPRECATE_MEMORY
#endif*/
#include <cstring>

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "Part.hpp"
#include "CircuitPart.hpp"

using namespace std;

CircuitPart* Part::GenerateCircuitPart(map<string, string> options) {
	CircuitPart* p = new CircuitPart(this);
	for (const auto& kv : options) { p->options.insert(kv); }
	for (const auto& kv : this->pins) {
		//Pin* pin = (Pin*)malloc(sizeof(Pin));
		Pin* pin = new Pin();
		memcpy(pin, kv.second, sizeof(Pin));
		p->pins.insert({ kv.first, pin });
	}
	return p;
}

DrawableVector * Part::DrawCircuit(CircuitPart *)
{
	return nullptr;
}

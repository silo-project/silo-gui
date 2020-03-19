#include <cstdint>
#include <map>
#include <string>

#include "CircuitPart.hpp"

#include "Position.hpp"
#include "Pin.hpp"

CircuitPart::CircuitPart(RootPart* pp) {
	partPointer = pp;
}

CircuitPart::~CircuitPart() {

}

#include <cstdint>
#include <map>
#include <string>

#include "Position.hpp"
#include "CircuitPart.hpp"
#include "Pin.hpp"

CircuitPart::CircuitPart(Part* pp) {
	partPointer = pp;
}

CircuitPart::~CircuitPart() {

}

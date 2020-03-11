#include "part.hpp"

Part::Part(int _uid, uint32_t _libraryid, uint32_t _partid, Position _pos) {
	uid = _uid;
	pid = PARTID_GENERATE(_libraryid, _partid);
	pos = _pos;
}

Part::~Part()
{

}

uint64_t generatePartID(uint32_t x, uint32_t y) { return PARTID_GENERATE(x, y); }
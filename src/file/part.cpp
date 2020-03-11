#include "part.hpp"

Part::Part(uint32_t _uid, uint32_t _partid) {
	uid = _uid;
	pid = PARTID_GENERATE(UINT32_MAX, _partid); // Means Local File Circuit
}

Part::Part(uint32_t _uid, uint32_t _libraryid, uint32_t _partid) {
	uid = _uid;
	pid = PARTID_GENERATE(_libraryid, _partid);
}

uint64_t generatePartID(uint32_t x, uint32_t y) { return PARTID_GENERATE(x, y); }
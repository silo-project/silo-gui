#ifndef PART_H
#define PART_H

#include <cstdint>

#define PARTID_GETLIBRARYID(a)	(((a) >> 32) & 0x00000000FFFFFFFF)
#define PARTID_GETPARTID(a)		((a) & 0x00000000FFFFFFFF)
#define PARTID_GENERATE(x, y)	((((uint64_t)(x)) << 32) | (y))

typedef uint64_t _PartID;

uint64_t generatePartID(uint32_t, uint32_t);

class Part {
protected:
	int uid;
	_PartID pid;

public:
	int getUID() { return uid; }
	uint32_t getLibraryID() { return PARTID_GETLIBRARYID(pid); }
	uint32_t getPartID() { return PARTID_GETPARTID(pid); }
	Part(uint32_t, uint32_t);
	Part(uint32_t, uint32_t, uint32_t);
	~Part();
};

#endif
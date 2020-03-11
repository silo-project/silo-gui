#ifndef PART_H
#define PART_H

#include <cstdint>

#include <map>

typedef uint64_t Position;

#define POSITION_GETX(a)		(((a) >> 32) & 0x00000000FFFFFFFF)
#define POSITION_GETY(a)		((a) & 0x00000000FFFFFFFF)
#define POSITION_GENERATE(x, y)	((((uint64_t)(x)) << 32) | (y))


typedef uint64_t _PartID;

#define PARTID_GETLIBRARYID(a)	(((a) >> 32) & 0x00000000FFFFFFFF)
#define PARTID_GETPARTID(a)		((a) & 0x00000000FFFFFFFF)
#define PARTID_GENERATE(x, y)	((((uint64_t)(x)) << 32) | (y))

uint64_t generatePartID(uint32_t, uint32_t);

class Part {
protected:
	int uid;
	_PartID pid;
	Position pos;

public:
	std::map<std::string, std::string> options;
	inline int getUID() { return uid; }
	inline _PartID getPartID() { return pid; }
	Part(int, uint32_t, uint32_t, Position);
	~Part();
};

#endif
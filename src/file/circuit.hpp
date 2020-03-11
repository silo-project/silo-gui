#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <map>
#include <set>
#include "part.hpp"
namespace _CircuitCmp {
	struct cmp {
		bool operator() (Part*, Part*) const;
	};
}

class Circuit {
public: enum Side { north = 1, south, east, west };
protected:
	std::string* name;
	std::string* label;
	Side labelup;
	std::string* labelfont;

public:
	const char* getName();
	const char* getLabel();
	Side getLabelUp();
	const char* getLabelFont();

	std::multimap<Position, Position> forward;
	std::multimap<Position, Position> reverse;

	Circuit(const char*, const char*, Side, const char*);
	~Circuit();
	std::set<Part*, _CircuitCmp::cmp> partSet;
};

#endif
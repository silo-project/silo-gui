#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include "part.hpp"

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

	Circuit(const char*, const char*, Side, const char*);
	~Circuit();
	std::vector<Part*> partVect;
};

#endif
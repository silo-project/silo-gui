#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

#include <string>

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
};

#endif
#ifndef __CIRCUIT_H__
#define __CIRCUIT_H__

namespace Circuit {
	enum Side {
		north, south, east, west
	};
}

class Circuit {
protected:
	std::string name;
	std::string label;
	Circuit::side labelup;

public:
	std::string getName();

	Circuit();
	~Circuit();
};

#endif
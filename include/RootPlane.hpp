#ifndef ROOTPLANE_H
#define ROOTPLANE_H

#include <map>

#include "RootPart.hpp"

class RootPlane {
public:
	std::vector<RootPartonRootPlane*> rootPartVector;
	std::map<wireID, WirePosition*> wirePositionMap;
	RootPlane();
	~RootPlane();
};

#endif
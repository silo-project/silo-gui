#include <iostream>
#include <string>
#include <set>

#include <cstdlib>

#include "../tinyxml2/tinyxml2.h"
#include "circreader.hpp"

using namespace std;

using namespace tinyxml2;

namespace CircReader {
	int readFile(char* file, std::set<Circuit*>* circuitSet) {
		XMLDocument doc;
		doc.LoadFile(file);
		XMLElement* project = doc.FirstChildElement("project");
		int circcount = 0;
		for (XMLElement* circuit = project->FirstChildElement("circuit"); circuit; circuit = circuit->NextSiblingElement("circuit")) {
			circuitSet->insert(readCirc(circuit));
			cout << "b" << endl;
			circcount++;
		}
		return circcount;
	}

	Circuit* readCirc(XMLElement* circuit) {
		const char* circname;
		const char* label;
		const char* slabelup;
		const char* labelfont;
		circuit->QueryStringAttribute("name", &circname);
		XMLElement* a = circuit->FirstChildElement("a");
		a = a->NextSiblingElement("a");
		a->QueryStringAttribute("val", &label);
		a = a->NextSiblingElement("a");
		a->QueryStringAttribute("val", &slabelup);
		a = a->NextSiblingElement("a");
		a->QueryStringAttribute("val", &labelfont);
		Circuit::Side labelup = (Circuit::Side)0;
		if (strcmp(slabelup, "north") == 0) labelup = Circuit::Side::north;
		else if (strcmp(slabelup, "south") == 0) labelup = Circuit::Side::south;
		else if (strcmp(slabelup, "east") == 0) labelup = Circuit::Side::east;
		else if (strcmp(slabelup, "west") == 0) labelup = Circuit::Side::west;
		return new Circuit(circname, label, labelup, labelfont);
	}
}
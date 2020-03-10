#include <iostream>

#include "../tinyxml2/tinyxml2.h"
#include "circreader.hpp"

using namespace std;

using namespace tinyxml2;

namespace CircReader {
	Circuit* read(char* file) {
		XMLDocument doc;
		doc.LoadFile(file);
		XMLElement* project = doc.FirstChildElement("project");
		for (XMLElement* circuit = project->FirstChildElement("circuit"); circuit; circuit = circuit->NextSiblingElement("circuit")) {
			const char* circname;
			circuit->QueryStringAttribute("name", &circname);
			circuit->
			cout << circname << endl;
		}
	}
}
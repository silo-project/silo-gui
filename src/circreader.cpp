#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <cstdlib>

#include "../tinyxml2/tinyxml2.h"
#include "circreader.hpp"
#include "librarymanager.hpp"
#include "partmanager.hpp"

using namespace std;

using namespace tinyxml2;

namespace CircReader {
	int uid = 0;
	const char * mainname;

	int readFile(char* file, std::vector<Circuit*>* circuitVector) {
		XMLDocument doc;
		doc.LoadFile(file);
		XMLElement* project = doc.FirstChildElement("project");
		project->FirstChildElement("main")->QueryStringAttribute("name", &mainname);
		for (XMLElement* library = project->FirstChildElement("lib"); library; library = library->NextSiblingElement("lib")) {
			const char* name; int id;
			library->QueryStringAttribute("desc", &name);
			library->QueryIntAttribute("name", &id);
			string sname(name);
			LibraryManager::regLibrary(name, id, LibraryManager::loadLibrary(name, id));
		}
		std::map<int, XMLElement*> xmlcircreadymap;
		int i = 0;
		for (XMLElement* circuit = project->FirstChildElement("circuit"); circuit; circuit = circuit->NextSiblingElement("circuit")) {
			xmlcircreadymap.insert({ i, circuit });
			i++;
		}

		int nc = 0;
		int ci = 0;
		while (xmlcircreadymap.size() != nc) {
			cout << "Trying " << ci << endl;
			if (xmlcircreadymap[ci] == NULL) continue;
			Circuit* readc = readCirc(xmlcircreadymap[ci], circuitVector);
			if (readc) {
				circuitVector->push_back(readc);
				xmlcircreadymap[ci] = NULL;
				nc++;
				cout << "Success " << ci << endl;
			} else {
				cout << "Fail " << ci << endl;
			}
			if (++ci == xmlcircreadymap.size()) ci = 0;
		}

		return circuitVector->size();
	}

	Circuit* readCirc(XMLElement* circuit, std::vector<Circuit*>* circuitVector) {
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
		Circuit* c = new Circuit(circname, label, labelup, labelfont);
		const char* cpos;
		const char* cname;
		int libnum;
		uint64_t pos;
		for (XMLElement* comp = circuit->FirstChildElement("comp"); comp; comp = comp->NextSiblingElement("comp")) {
			libnum = -1;
			comp->QueryIntAttribute("lib", &libnum);
			comp->QueryStringAttribute("loc", &cpos);
			comp->QueryStringAttribute("name", &cname);
			char* cposv;
			strcpy(cposv, cpos);
			pos = POSITION_GENERATE(atoi(strtok(cposv, "(,)")), atoi(strtok(NULL, "(,)")));
			Circuit fc(cname, NULL, (Circuit::Side)0, NULL);
			std::vector<Circuit*>::iterator i = std::find_if(circuitVector->begin(), circuitVector->end(),
				[cname](Circuit* c) { return strcmp(c->getName(), cname) == 0; }
			);
			_PartID pid = UINT64_MAX;
			if (libnum == -1 && i == circuitVector->end()) {
				return NULL;
			} else if (i != circuitVector->end()) {
				pid = PARTID_GENERATE(UINT32_MAX, circuitVector->begin() - i);
			} else {
				pid = LibraryManager::findPartManager(libnum)->findPartID(cname);
			}
			Part* p = new Part(uid++, pid, pos);
			for (XMLElement* copt = comp->FirstChildElement("a"); copt; copt = copt->NextSiblingElement("a")) {
				const char* k; const char* v;
				copt->QueryStringAttribute("name", &k);
				copt->QueryStringAttribute("val", &v);
				p->options.insert({string(k), string(v)});
			}
			c->partSet.insert(p);
		}
		return c;
	}
}
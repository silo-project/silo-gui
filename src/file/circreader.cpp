#include <iostream>
#include <string>
#include <vector>

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
			library->QueryStringAttribute("name", &id);
			string sname(name);
			LibraryManager::regLibrary(name, id, LibraryManager::loadLibrary());
		}
		int circcount = 0;
		for (XMLElement* circuit = project->FirstChildElement("circuit"); circuit; circuit = circuit->NextSiblingElement("circuit")) {
			circuitVector->push_back(readCirc(circuit));
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
			Part* p = new Part(uid++, LibraryManager::findPartManager(libnum)->findPartID(cname), pos);
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
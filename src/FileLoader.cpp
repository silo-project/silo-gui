#include "tinyxml2.h"

#include "FileLoader.hpp"
#include "type.hpp"
#include "Part.hpp"

using namespace tinyxml2;

int FileLoader::LoadCircuit(XMLElement* circuit) {
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
	Side labelup = (Side)0;
	if (strcmp(slabelup, "north") == 0) labelup = Side::NORTH;
	else if (strcmp(slabelup, "south") == 0) labelup = Side::SOUTH;
	else if (strcmp(slabelup, "east") == 0) labelup = Side::EAST;
	else if (strcmp(slabelup, "west") == 0) labelup = Side::WEST;
	Part* p = new Part();

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
		Circuit fc(cname, NULL, (Side)0, NULL);
		std::vector<Circuit*>::iterator i = std::find_if(circuitVector->begin(), circuitVector->end(),
			[cname](Circuit* c) { return strcmp(c->getName(), cname) == 0; }
		);
		_PartID pid = UINT64_MAX;
		if (libnum == -1 && i == circuitVector->end()) {
			return NULL;
		}
		else if (i != circuitVector->end()) {
			pid = PARTID_GENERATE(UINT32_MAX, circuitVector->begin() - i);
		}
		else {
			pid = LibraryManager::findPartManager(libnum)->findPartID(cname);
		}
		Part* p = new Part(uid++, pid, pos);
		for (XMLElement* copt = comp->FirstChildElement("a"); copt; copt = copt->NextSiblingElement("a")) {
			const char* k; const char* v;
			copt->QueryStringAttribute("name", &k);
			copt->QueryStringAttribute("val", &v);
			p->options.insert({ string(k), string(v) });
		}
		c->partSet.insert(p);
	}
	return c;
}
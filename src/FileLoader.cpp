#include <algorithm>
#include <string>

#include "tinyxml2.h"

#include "type.hpp"

#include "FileLoader.hpp"
#include "RootPart.hpp"
#include "RootPlane.hpp"
#include "LibraryManager.hpp"

using std::string;
using std::vector;
using namespace tinyxml2;

Library* FileLoader::LoadDefaultLibrary(const char* name) {
	Library* dl = new Library();
	if (strcmp(name, "#Wiring") == 0) {
		dl->rootPartVector.push_back({ new RootPart() }); // TODO DAKDJSHGAEGASD
	}
	else if (strcmp(name, "#Gates") == 0) {

	}
	else if (strcmp(name, "#Plexers") == 0) {

	}
	else if (strcmp(name, "#Arithmetic") == 0) {

	}
	else if (strcmp(name, "#Memory") == 0) {

	}
	else if (strcmp(name, "#I/O") == 0) {

	}
	else if (strcmp(name, "#Base") == 0) {

	}
	return dl;
}

int FileLoader::LoadFile(const char* file, LibraryManager* rootlm, int rootpartid) {
	XMLDocument doc;
	doc.LoadFile(file);
	XMLElement* project = doc.FirstChildElement("project");
	LibraryManager* locallm = new LibraryManager();
	for (XMLElement* library = project->FirstChildElement("lib"); library; library = library->NextSiblingElement("lib")) {
		const char* name; int id;
		library->QueryStringAttribute("desc", &name);
		library->QueryIntAttribute("name", &id);
		string sname(name);
			if (name[0] == '#') { // Default Library
				vector<string>::iterator frlm = std::find(
					rootlm->libraryNameVector.begin(), rootlm->libraryNameVector.end(), sname);
				vector<string>::iterator fllm = std::find(
					locallm->libraryNameVector.begin(), locallm->libraryNameVector.end(), sname);
				bool lerlm = frlm == rootlm->libraryNameVector.end(); // NOT EXISTS in Root LibraryManager
				bool lellm = fllm == locallm->libraryNameVector.end(); // NOT EXISTS in Local LibraryManager
				Library* dl = nullptr;
				if (!lerlm) {
					dl = LoadDefaultLibrary(name); // Never Created

					locallm->libraryNameVector.insert(locallm->libraryNameVector.begin() + id, sname);
					locallm->libraryVector.insert(locallm->libraryVector.begin() + id, dl);
					rootlm->libraryNameVector.push_back(sname);
					rootlm->libraryVector.push_back(dl);
				} else {
					if (!lellm) { // Exists in Root, Not in Local
						locallm->libraryNameVector.insert(locallm->libraryNameVector.begin() + id, sname);
						locallm->libraryVector.insert(locallm->libraryVector.begin() + id,
							rootlm->libraryVector.at(static_cast<int>(frlm - rootlm->libraryNameVector.begin())));
					}
				}
			}
			else { // File Library
				LoadFile(name, rootlm, rootpartid);
			}/*
		} else {
			locallm->libraryNameMap.insert({ name, id });
			locallm->libraryMap.insert({id, rootlm->libraryMap.find(rootlm->libraryNameMap.find(name)->second)->second});
		}*/
	}
	for (XMLElement* circuit = project->FirstChildElement("circuit"); circuit; circuit = circuit->NextSiblingElement("circuit")) {
		RootPartbyRootPlane* rpc = LoadCircuit(circuit, locallm);
		vector<RootPartonRootPlane*> prpv = rpc->Plane.rootPartVector;
		// TODO: GOD DAMN
		rootlm->libraryMap[UINT32_MAX]->rootPartMap.insert({ rootpartid, rpc });
		rootpartid++;
	}
}

RootPartbyRootPlane* FileLoader::LoadCircuit(const XMLElement* circuit, LibraryManager* lm) {
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
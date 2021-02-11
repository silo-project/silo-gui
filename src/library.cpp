//
// Created by penta on 2020-11-24.
//

#include <string>
#include <map>
#include <vector>

#include <tinyxml2.h>

#include <miniz.h>

#include "library.h"

using namespace tinyxml2;

cLibraryManager::cLibraryManager() {
    this->openZipLibrary("", "#Wiring");
    this->openZipLibrary("", "#Gates");
    this->openZipLibrary("", "#Plexers");
    this->openZipLibrary("", "#Arithmetic");
    this->openZipLibrary("", "#Memory");
    this->openZipLibrary("", "#I/O");
    this->openZipLibrary("", "#Base");
    this->libraryMap.find("#Wiring")->second->mapAbstractPart.insert(std::pair<std::string, AbstractPart*>("Tunnel", new AbstractTunnelPart()));
}

// WireID
// 0, 1, ...    : for "Wire"s
// -1, -2, ...  : for "Tunnel"s


void LibraryManager::connectWires(AbstractPart* thispart, std::map<WireNetID, WireNet*> &mapWireNetIDP,
        std::map<WireID, position> &mapWireIDPosA, std::map<WireID, position> &mapWireIDPosB,
        std::map<std::string, std::vector<position>*> &mapLabelvectorPosition, WireID &nowLabelID,
        WireNetID &nowWireNetID, std::vector<position> &vectorPositionnowPropagate) {
    std::vector<position> vectorPositionnextPropagate;
    for(auto t: vectorPositionnowPropagate) {
        for(const auto& iL: mapLabelvectorPosition) {
            for(auto iP: *(iL.second)) {
                if(iP == t) {
                    for(auto itP: *(iL.second)) {
                        vectorPositionnextPropagate.push_back(itP);
                        mapWireNetIDP.find(nowWireNetID)->second->mapA.insert(std::pair<WireID, position>(nowLabelID, t));
                        mapWireNetIDP.find(nowWireNetID)->second->mapB.insert(std::pair<WireID, position>(nowLabelID--, itP));
                    }
                    auto itL = mapLabelvectorPosition.find(iL.first);
                    delete itL->second;
                    mapLabelvectorPosition.erase(itL);
                }
            }
        }
        for(auto iA: mapWireIDPosA) {
            auto wID = iA.first;
            auto iB = mapWireIDPosB.find(wID);
            if(iA.second == t) {
                mapWireNetIDP.find(nowWireNetID)->second->mapB.insert(std::pair<WireID, position>(wID, iB->second));
                vectorPositionnextPropagate.push_back(iB->second);
                mapWireIDPosA.erase(mapWireIDPosA.find(wID));
                mapWireIDPosB.erase(iB);
            } else if(iB->second == t) {
                mapWireNetIDP.find(nowWireNetID)->second->mapA.insert(std::pair<WireID, position>(wID, iA.second));
                vectorPositionnextPropagate.push_back(iA.second);
                mapWireIDPosA.erase(mapWireIDPosA.find(wID));
                mapWireIDPosB.erase(iB);
            }
        }
    }
    if(vectorPositionnextPropagate.empty()) {
        if(mapWireIDPosA.empty()) return;
        else {
            ++nowWireNetID;
            mapWireNetIDP.insert(std::pair<WireNetID, WireNet*>(nowWireNetID, new WireNet()));
            nowLabelID = -1u;
        }
    }

    connectWires(thispart, mapWireNetIDP, mapWireIDPosA, mapWireIDPosB, mapLabelvectorPosition, nowLabelID, nowWireNetID, vectorPositionnowPropagate);
}

Library* LibraryManager::openCircLibrary(const std::string &filepath, const std::string &name) { // "C:/Example.circ"
    std::map<int, std::string> mapLibIDName;

    Library* lib = searchLibrary(name);

    if(lib == nullptr) lib = new Library();
    else if(lib->type != eLibraryType::LibraryType_UNDEF) return lib;

    lib->type = LibraryType::LibraryType_Circ;
    XMLDocument doc;
    doc.LoadFile(filepath.c_str());

    XMLElement* tagproject = doc.FirstChildElement("project");

    {
        XMLElement *taglib = tagproject->FirstChildElement("lib");
        while (taglib != nullptr) {
            taglib = taglib->NextSiblingElement("lib");
            const char *libname = nullptr;
            taglib->QueryStringAttribute("desc", &libname);
            std::string libsname(libname);
            Library *libpointer = searchLibrary(libsname);
            if (libpointer == nullptr) {
                libpointer = new Library();
                putLibrary(libsname, libpointer);
            }
            lib->parents.push_back(libsname);
            libpointer->childs.push_back(name);
            int num = -1;
            taglib->QueryIntAttribute("name", &num);
            mapLibIDName.insert(std::pair(num, libsname));
        }
    }

    XMLElement* tagcircuit = tagproject->FirstChildElement("circuit");
    while (tagcircuit != nullptr) {
        tagcircuit = tagcircuit->NextSiblingElement("circuit");
        const char * circuitname = nullptr;
        tagcircuit->QueryStringAttribute("name", &circuitname);
        std::string libsname(circuitname);
        auto* thispart = new AbstractCircPart();

        {
            XMLElement *taga = tagcircuit->FirstChildElement("a");
            while (taga != nullptr) {
                taga = taga->NextSiblingElement("a");
                const char *aname = nullptr;
                const char *aval = nullptr;
                taga->QueryStringAttribute("name", &aname);
                taga->QueryStringAttribute("val", &aval);
                thispart->mapAbstractAttribute.insert(
                        std::pair<std::string, std::string *>(std::string(aname), new std::string(aval)));
            }
        }

        std::map<std::string, std::vector<position>*> mapLabelvectorPosition;

        {
            XMLElement *tagcomp = tagcircuit->FirstChildElement("comp");
            while (tagcomp != nullptr) {
                tagcomp = tagcomp->NextSiblingElement("comp");
                int libnum = -1;
                const char *compname = nullptr;
                const char *poschar = nullptr;
                tagcomp->QueryIntAttribute("lib", &libnum);
                tagcomp->QueryStringAttribute("loc", &poschar);
                tagcomp->QueryStringAttribute("name", &compname);

                AbstractPart* ds = nullptr;

                {
                    if (libnum == -1) { // THIS FILE
                        auto i = lib->mapAbstractPart.find(compname);
                        if (i != lib->mapAbstractPart.end()) {
                            ds = i->second;
                        } else {
                            ds = new AbstractPart();
                            lib->mapAbstractPart.insert(
                                    std::pair<std::string, AbstractPart *>(std::string(compname), ds));
                        }
                    } else {
                        auto q = searchLibrary(mapLibIDName.find(libnum)->second);
                        // 무조건, UNDEFined Library 포인터라도 뱉는다.

                        auto i = q->mapAbstractPart.find(compname);
                        if (i != q->mapAbstractPart.end()) {
                            ds = i->second;
                        } else {
                            ds = new AbstractPart();
                            q->mapAbstractPart.insert(
                                    std::pair<std::string, AbstractPart *>(std::string(compname), ds));
                        }
                    }
                }

                {
                    XMLElement *tagda = tagcomp->FirstChildElement("a");
                    while (tagda != nullptr) {
                        tagda = tagda->NextSiblingElement("a");
                        const char *daname = nullptr;
                        const char *daval = nullptr;
                        tagda->QueryStringAttribute("name", &daname);
                        tagda->QueryStringAttribute("val", &daval);
                        ds->mapAttribute.insert(
                                std::pair<std::string, std::string *>(std::string(daname), new std::string(daval)));
                    }
                }

                auto pos = Position::fromLoc(poschar);

                auto it = mapLibIDName.find(libnum);
                if(it != mapLibIDName.end() && it->second == "#Wiring") {
                    if(strcmp(compname, "Tunnel") == 0) {
                        // TODO: Process Tunnel
                        ds = searchLibrary("#Wiring")->mapAbstractPart.find("Tunnel")->second;
                        auto label = *(ds->mapAttribute.find("label")->second);
                        auto ip = mapLabelvectorPosition.find(label);
                        if (ip == mapLabelvectorPosition.end()) {
                            auto t = new std::vector<position>;
                            t->push_back(pos);
                            mapLabelvectorPosition.insert(std::pair<std::string, std::vector<position> *>(label, t));
                        }
                    }
                }

                thispart->mapAbstractPart.insert(std::pair(pos, ds));
            }
        }

        std::map<WireID, position> mapWireIDPosF, mapWireIDPosT;
        WireID dsa = 0;

        {
            XMLElement *tagwire = tagcircuit->FirstChildElement("wire");
            while (tagwire != nullptr) {
                tagwire = tagwire->NextSiblingElement("a");
                const char *wf = nullptr;
                const char *wt = nullptr;
                tagwire->QueryStringAttribute("from", &wf);
                tagwire->QueryStringAttribute("to", &wt);
                mapWireIDPosF.insert(std::pair<WireID, position>(dsa, Position::fromLoc(wf)));
                mapWireIDPosT.insert(std::pair<WireID, position>(dsa, Position::fromLoc(wt)));
                dsa++;
            }

            if (dsa > 0 || !mapLabelvectorPosition.empty()) {
                std::map<WireID, position> mapWireIDPosA(mapWireIDPosF), mapWireIDPosB(mapWireIDPosT);

                std::vector<position> vectorPositionnextPropagate;

                auto iA = mapWireIDPosA.begin();
                auto iID = iA->first;
                vectorPositionnextPropagate.push_back(iA->second);
                mapWireIDPosA.erase(iA);
                auto iB = mapWireIDPosB.find(iID);
                vectorPositionnextPropagate.push_back(iB->second);
                mapWireIDPosB.erase(iB);

                std::map<WireNetID, WireNet *> mapWireNetIDP;
                mapWireNetIDP.insert(std::pair<WireNetID, WireNet *>(0, new WireNet()));
                thispart->vectorWireNetID.push_back(0);

                mapWireNetIDP.find(0)->second->mapA.insert(std::pair<WireID, position>(iID, iA->second));
                mapWireNetIDP.find(0)->second->mapB.insert(std::pair<WireID, position>(iID, iB->second));

                WireNetID nowWireNetID = 0;
                WireID nowLabelID = -1u;

                connectWires(thispart, mapWireNetIDP,
                        mapWireIDPosA, mapWireIDPosB,
                        mapLabelvectorPosition, nowLabelID,
                        nowWireNetID, vectorPositionnextPropagate);

                for(const auto& s: mapLabelvectorPosition) {
                    ++nowWireNetID;
                    WireID f = s.second->at(0);
                    for(auto sr: *(s.second)) {
                        if(sr == f) continue;
                        mapWireNetIDP.find(nowWireNetID)->second->mapA.insert(std::pair<WireID, position>(nowLabelID, sr));
                        mapWireNetIDP.find(nowWireNetID)->second->mapB.insert(std::pair<WireID, position>(nowLabelID--, f));
                    }
                    delete s.second;
                    mapLabelvectorPosition.erase(mapLabelvectorPosition.find(s.first));
                }


            }
        }

        lib->mapAbstractPart.insert(std::pair(libsname, dynamic_cast<AbstractPart*>(thispart)));

        for(const auto& t: mapLabelvectorPosition) delete t.second;
    }


    
    return lib;
}

Library* LibraryManager::openZipLibrary(const std::string &filepath, const std::string &name) { // "C:/Example.zip"
    Library* lib = searchLibrary(name);

    if(lib == nullptr) lib = new Library();
    else if(lib->type != eLibraryType::LibraryType_UNDEF) return lib;

    lib->type = LibraryType::LibraryType_Zip;

    return lib;
}

Library* LibraryManager::searchLibrary(const std::string &name) {
    auto lib = this->libraryMap.find(name);
    return (lib == this->libraryMap.end()) ? nullptr : lib->second;
}

void LibraryManager::putLibrary(const std::string &name, Library* lib) {
    this->libraryMap.insert(std::pair<std::string, Library*>(name, lib));
}

bool cLibrary::isReady(LibraryManager &lm) {
    if(this->type == eLibraryType::LibraryType_UNDEF) return false;
    for(const auto& t: this->parents)
        if(!lm.searchLibrary(t)->isReady(lm)) return false;
    for(const auto& t: this->mapAbstractPart)
        if(t.second->type == ePartType::PartType_UNDEF) return false;
    return true;
}

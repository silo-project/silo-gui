//
// Created by penta on 2020-11-24.
//

#include <fstream>
#include <string>
#include <map>
#include <vector>

#include <rapidxml.hpp>

#include <miniz.h>

#include "library.h"

using namespace rapidxml;

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
    xml_document<> doc;
    std::ifstream fp(filepath.c_str());

    std::vector<char> buffer((std::istreambuf_iterator<char>(fp)), std::istreambuf_iterator<char>( ));
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);

    xml_node<>* tagproject = doc.first_node("project");

    {
        xml_node<>* taglib = tagproject->first_node("lib");
        while (taglib != nullptr) {
            taglib = taglib->next_sibling("lib");
            const char *libname = taglib->first_attribute("desc")->value();
            std::string libsname(libname);
            Library *libpointer = searchLibrary(libsname);
            if (libpointer == nullptr) {
                libpointer = new Library();
                putLibrary(libsname, libpointer);
            }
            lib->parents.push_back(libsname);
            libpointer->childs.push_back(name);
            int num = atoi(taglib->first_attribute("name")->value());
            mapLibIDName.insert(std::pair(num, libsname));
        }
    }

    xml_node<>* tagcircuit = tagproject->first_node("circuit");
    while (tagcircuit != nullptr) {
        tagcircuit = tagcircuit->next_sibling("circuit");
        const char * circuitname = tagcircuit->first_attribute("name")->value();
        std::string libsname(circuitname);
        auto* thispart = new AbstractCircPart();

        {
            xml_node<>* taga = tagcircuit->first_node("a");
            while (taga != nullptr) {
                taga = taga->next_sibling("a");
                const char *aname = taga->first_attribute("name")->value();
                const char *aval = taga->first_attribute("val")->value();
                thispart->mapAbstractAttribute.insert(
                        std::pair<std::string, std::string *>(std::string(aname), new std::string(aval)));
            }
        }

        std::map<std::string, std::vector<position>*> mapLabelvectorPosition;

        {
            xml_node<>* tagcomp = tagcircuit->first_node("comp");
            while (tagcomp != nullptr) {
                tagcomp = tagcomp->next_sibling("comp");
                int libnum = atoi(tagcomp->first_attribute("lib")->value());
                const char *compname = tagcomp->first_attribute("name")->value();
                const char *poschar = tagcomp->first_attribute("loc")->value();

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
                    xml_node<>* tagda = tagcomp->first_node("a");
                    while (tagda != nullptr) {
                        tagda = tagda->next_sibling("a");
                        const char *daname = tagda->first_attribute("name")->value();
                        const char *daval = tagda->first_attribute("val")->value();
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
            xml_node<>* tagwire = tagcircuit->first_node("wire");
            while (tagwire != nullptr) {
                tagwire = tagwire->next_sibling("a");
                const char *wf = tagwire->first_attribute("from")->value();
                const char *wt = tagwire->first_attribute("to")->value();
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

    fp.close();
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

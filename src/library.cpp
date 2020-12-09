//
// Created by penta on 2020-11-24.
//

#include <string>
#include <filesystem>

#include <tinyxml2.h>

#include "library.h"

using namespace tinyxml2;

Library* LibraryManager::openCircLibrary(const std::string &filepath, Library* lib) { // "C:/Example.circ"
    std::map<int, Library*> libnumbernamemap;
    if(lib == nullptr) lib = new Library();
    lib->type = LibraryType::LibraryType_Circ;
    XMLDocument doc;
    doc.LoadFile(filepath.c_str());

    XMLElement* tagproject = doc.FirstChildElement("project");

    XMLElement* taglib = tagproject->FirstChildElement("lib");
    while (taglib != nullptr) {
        taglib = taglib->NextSiblingElement("lib");
        const char * libname = nullptr;
        taglib->QueryStringAttribute("desc", &libname);
        std::string libsname(libname);
        Library* libpointer = searchLibrary(libsname);
        if(libpointer == nullptr) {
            libpointer = new Library();
            putLibrary(libsname, libpointer);
        }
        lib->parents.push_back(libpointer);
        libpointer->childs.push_back(lib);
        int num = -1;
        taglib->QueryIntAttribute("name", &num);
        libnumbernamemap.insert(std::pair(num, libpointer));
    }

    XMLElement* tagcircuit = tagproject->FirstChildElement("circuit");
    while (tagcircuit != nullptr) {
        tagcircuit = tagcircuit->NextSiblingElement("circuit");
        const char * circuitname = nullptr;
        tagcircuit->QueryStringAttribute("name", &circuitname);
        std::string libsname(circuitname);
        auto* thispart = new AbstractCircPart();
        thispart->mapAbstractPart;

        lib->mapAbstractPart.insert(std::pair<std::string, AbstractPart*>(libsname, static_cast<AbstractPart*>(thispart)));
    }


    
    return lib;
}

Library* LibraryManager::openZipLibrary(const std::string &filepath, Library* lib) { // "C:/Example.zip"
    if(lib == nullptr) lib = new Library();
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

bool cLibrary::isReady() {
    bool ready = this->type != eLibraryType::LibraryType_UNDEF;
    for(const auto& t : this->parents)
        ready = ready & t->isReady();
    return ready;
}

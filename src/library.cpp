//
// Created by penta on 2020-11-24.
//

#include <string>
#include <filesystem>

#include "library.h"

CircLibrary* LibraryManager::openCircLibrary(const std::filesystem::path &filepath) { // "C:/Example.circ"
    auto* lib = new CircLibrary();
    lib->type = LibraryType::LibraryType_Circ;
    return lib;
}

ZipLibrary* LibraryManager::openZipLibrary(const std::filesystem::path &filepath) { // "C:/Example.zip"
    auto* lib = new ZipLibrary();
    lib->type = LibraryType::LibraryType_Zip;
    return lib;
}

const Library* LibraryManager::searchLibrary(const std::string &name) {
    auto lib = this->libraryMap.find(name);
    return (lib == this->libraryMap.end()) ? nullptr : lib->second;
}

void LibraryManager::putLibrary(const std::string &name, const Library* lib) {
    this->libraryMap.insert(std::pair<std::string, const Library*>(name, lib));
}
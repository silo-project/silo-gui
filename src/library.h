//
// Created by penta on 2020-11-24.
//

#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include "part.h"

#ifndef SILO_GUI_LIBRARY_H
#define SILO_GUI_LIBRARY_H

typedef enum eLibraryType {
    LibraryType_Abstract,
    LibraryType_Circ = 1,
    LibraryType_Zip
} LibraryType;

typedef class cLibrary Library;

class cLibrary {
public:
    LibraryType type = eLibraryType::LibraryType_Abstract;
    std::filesystem::path path = "";
    std::vector<Library*> parents;
    std::vector<Library*> childs;
    std::map<std::string, Part*> partMap;
    bool isReady();
};

typedef class LibraryManager {
protected:
    std::map<std::string, Library*> libraryMap;
public:
    Library* openCircLibrary(const std::string &filepath, Library* lib = nullptr);
    Library* openZipLibrary(const std::string &filepath, Library* lib = nullptr);
    Library* searchLibrary(const std::string& name);
    void putLibrary(const std::string& name, Library* lib);
} LibraryManager;


#endif //SILO_GUI_LIBRARY_H

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
    LibraryType type;
    std::filesystem::path filepath = "";
    std::vector<Library*> parents;
    std::vector<Library*> childs;
};

typedef class cZipLibrary : public Library {
public:
    std::filesystem::path folderpath = "";
    std::map<std::string, ComputePart*> partMap;
} ZipLibrary;

typedef class cCircLibrary : public Library {
public:
    std::map<std::string, CircPart*> partMap;
} CircLibrary;

typedef class LibraryManager {
protected:
    std::map<std::string, const Library*> libraryMap;
public:
    static CircLibrary* openCircLibrary(const std::filesystem::path &filepath);
    static ZipLibrary* openZipLibrary(const std::filesystem::path &filepath);
    const Library* searchLibrary(const std::string& name);
    void putLibrary(const std::string& name, const Library* lib);
} LibraryManager;


#endif //SILO_GUI_LIBRARY_H

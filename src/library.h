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
    LibraryType_UNDEF = 0,
    LibraryType_Circ = 1,
    LibraryType_Zip
} LibraryType;

typedef class cLibrary Library;

class cLibrary {
public:
    LibraryType type = eLibraryType::LibraryType_UNDEF;
    std::filesystem::path path = "";
    std::vector<std::string> parents;
    std::vector<std::string> childs;
    std::map<std::string, AbstractPart*> mapAbstractPart;
    bool isReady();
};

typedef class LibraryManager {
private:
    static void connectWires(AbstractPart* thispart, std::map<WireNetID, WireNet*> &mapWireNetIDP,
            std::map<WireID, position> &mapWireIDPosA, std::map<WireID, position> &mapWireIDPosB,
            WireNetID nwwnetid, std::vector<position> &vectorPositionnowPropagate);
protected:
    std::map<std::string, Library*> libraryMap;
public:
    Library* openCircLibrary(const std::string &filepath, const std::string &name);
    Library* openZipLibrary(const std::string &filepath, const std::string &name);
    Library* searchLibrary(const std::string& name);
    void putLibrary(const std::string& name, Library* lib);
} LibraryManager;


#endif //SILO_GUI_LIBRARY_H

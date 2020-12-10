//
// Created by penta on 2020-11-24.
//

#include <map>
#include <string>

#include "wirenet.h"

#ifndef SILO_GUI_PART_H
#define SILO_GUI_PART_H

struct NODE;

class cAbstractPart;
class cAbstractCircPart;
class cAbstractComputePart;

typedef unsigned int portID;

typedef uint64_t position;

namespace Position {
    position fromLoc(const char * loc);
    uint32_t getX(position p);
    uint32_t getY(position p);
}

typedef enum ePartType {
    PartType_UNDEF = 0,
    PartType_Circ = 1,
    PartType_Zip
} PartType;

typedef class cAbstractPart {
public:
    PartType type;
    std::map<std::string, std::string> mapAbstractAttribute;
    std::map<portID, WireNetID> mapWireNetID;
    std::string draw = "";
    void(* function)(NODE*) = nullptr; // Only for ComputePart
    std::map<position, cAbstractPart*> mapAbstractPart; // Only for CircPart
} AbstractPart;

typedef class cAbstractComputePart : public AbstractPart {
public:
    cAbstractComputePart();
} AbstractComputePart;

typedef class cAbstractCircPart : public AbstractPart {
public:
    cAbstractCircPart();
} AbstractCircPart;

#endif //SILO_GUI_PART_H

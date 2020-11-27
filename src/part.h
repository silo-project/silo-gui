//
// Created by penta on 2020-11-24.
//

#include <map>
#include <string>

#include "wirenet.h"

#ifndef SILO_GUI_PART_H
#define SILO_GUI_PART_H

struct NODE;

typedef unsigned int portID;

typedef struct sPosition {
    unsigned int x, y;

    bool operator<(const sPosition& rhs) const {
        return (this->x == rhs.x)? (this->y < rhs.y) : (this->x < rhs.x);
    }
} Position;

typedef enum ePartType {
    PartType_Circ = 1,
    PartType_Zip
} PartType;

typedef struct sAttribute {
    std::string name, value;
} Attribute;

typedef class cPart {
public:
    PartType type;
    std::map<std::string, Attribute> attributeMap;
    std::map<portID, WireNet*> wireNetMap;
    std::string draw = "";
} Part;

typedef class cComputePart : public Part {
    void(* function)(NODE*) = nullptr;
} ComputePart;

typedef class cCircPart : public Part {
    std::map<Position, Part*> partMap;
} CircPart;

#endif //SILO_GUI_PART_H

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
class cPart;
class cCircPart;
class cComputePart;

typedef unsigned int portID;

typedef struct sPosition {
    unsigned int x, y;

    bool operator<(const sPosition& rhs) const {
        return (this->x == rhs.x)? (this->y < rhs.y) : (this->x < rhs.x);
    }
} Position;

typedef enum ePartType {
    PartType_UNDEF = 0,
    PartType_Circ = 1,
    PartType_Zip
} PartType;

typedef struct sAttribute {
    std::string name, value;
} Attribute;

typedef class cPart {
public:
    PartType type;
    std::map<std::string, Attribute> mapAttribute;
    std::map<portID, WireNet*> mapWireNet;
    std::string draw = "";
} Part;

typedef class cComputePart : public Part {
public:
    explicit cComputePart(const class cAbstractComputePart *rootpart);
    void(* function)(NODE*) = nullptr;
} ComputePart;

typedef class cCircPart : public Part {
public:
    explicit cCircPart(const class cAbstractCircPart *rootpart);
    std::map<Position, Part*> mapPart;
} CircPart;

typedef class cAbstractPart {
public:
    PartType type;
    std::map<std::string, Attribute> mapAbstractAttribute;
    std::map<portID, WireNetID> mapWireNetID;
    std::string draw = "";
} AbstractPart;

typedef class cAbstractComputePart : public AbstractPart {
public:
    cAbstractComputePart();
    void(* function)(NODE*) = nullptr;
} AbstractComputePart;

typedef class cAbstractCircPart : public AbstractPart {
public:
    cAbstractCircPart();
    std::map<Position, AbstractPart*> mapAbstractPart;
} AbstractCircPart;

#endif //SILO_GUI_PART_H

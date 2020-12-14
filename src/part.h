//
// Created by penta on 2020-11-24.
//

#include <map>
#include <string>
#include <vector>

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
    position fromLoc(const char* loc); // (A,B)
    position fromPin(const char* pin); //  A,B
    uint32_t getX(position p);
    uint32_t getY(position p);
}

typedef enum ePartType {
    PartType_UNDEF = 0,
    PartType_Circ = 1,
    PartType_Zip,
    PartType_Tunnel
} PartType;

typedef class cAbstractPart {
public:
    PartType type;
    std::vector<WireNetID> vectorWireNetID; // 자신 파츠 안에 WireNetID가 몇 번까지 부여되는가

public:
    std::map<std::string, std::string*> mapAbstractAttribute; // 자신이 부모 파츠에게 줄 기본 속성
    std::map<std::string, std::string*> mapAttribute; // 부모 파츠가 본 자신의 속성
    std::map<portID, WireNetID> mapWireNetID; // 부모 파츠에서 보면 자신의 어느 포트가 어디 물려 있는가, 여기서 WireNetID는 부모 파츠별로 0부터 새로 시작한다.
    std::string draw = ""; // 임시

public:
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

typedef class cAbstractTunnelPart : public AbstractPart {
public:
    cAbstractTunnelPart();
} AbstractTunnelPart;

#endif //SILO_GUI_PART_H

//
// Created by penta on 2020-11-24.
//

#include <map>
#include <cstdint>

#ifndef SILO_GUI_WIRENET_H
#define SILO_GUI_WIRENET_H

typedef uint64_t position;
typedef unsigned int WireNetID;
typedef unsigned int WireID;

typedef class cWireNet {
public:
    std::map<WireID, position> mapA, mapB;
} WireNet;


#endif //SILO_GUI_WIRENET_H

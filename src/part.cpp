//
// Created by penta on 2020-11-24.
//

#include "part.h"

cAbstractCircPart::cAbstractCircPart()       { this->type = ePartType::PartType_Circ; }
cAbstractComputePart::cAbstractComputePart() { this->type = ePartType::PartType_Zip;  }

position Position::fromLoc(const char * loc) {
    return (atoi(loc + 1) << 32) | atoi(strchr(loc, ',') + 1);
}

uint32_t Position::getX(position p) {
    return (p >> 32) & 0x00000000FFFFFFFFul;
}

uint32_t Position::getY(position p) {
    return p & 0x00000000FFFFFFFFul;
}

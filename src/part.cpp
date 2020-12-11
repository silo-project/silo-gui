//
// Created by penta on 2020-11-24.
//

#include "part.h"

cAbstractCircPart::cAbstractCircPart()       { this->type = ePartType::PartType_Circ; }
cAbstractComputePart::cAbstractComputePart() { this->type = ePartType::PartType_Zip;  }

position Position::fromLoc(const char* loc) {
    return (((uint64_t)atoi(loc + 1)) << 32u) | ((uint32_t)atoi(strchr(loc, ',') + 1));
}

position Position::fromPin(const char* pin) {
    return (((uint64_t)atoi(pin)) << 32u) | ((uint32_t)atoi(strchr(pin, ',') + 1));
}

uint32_t Position::getX(position p) {
    return (p >> 32u) & 0x00000000FFFFFFFFull;
}

uint32_t Position::getY(position p) {
    return p & 0x00000000FFFFFFFFull;
}

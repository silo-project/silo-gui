//
// Created by penta on 2020-11-24.
//

#include "part.h"

/*cCircPart::cCircPart(const AbstractCircPart* rootpart) {
    this->type = ePartType::PartType_Circ;
    for(auto p: rootpart->mapAbstractPart) {
        auto c = p.second;
        Part* r = nullptr;

        switch(c->type) {
            case ePartType::PartType_UNDEF:
                continue;
            case ePartType::PartType_Circ:
                r = new CircPart(reinterpret_cast<AbstractCircPart*>(c));
                break;

            case ePartType::PartType_Zip:
                r = new ComputePart(reinterpret_cast<AbstractComputePart*>(c));
                break;
        }

        this->mapPart.insert(std::pair<Position, Part*> (p.first, r));
    }

    for(const auto& t: rootpart->mapAbstractAttribute)
        this->mapAttribute.insert(std::pair<std::string, Attribute>(t.first, t.second)); //TODO: COPY t.second
    this->draw = rootpart->draw;
}

cComputePart::cComputePart(const AbstractComputePart* rootpart) {
    this->type = ePartType::PartType_Zip;
    this->function = rootpart->function;
    for(const auto& t: rootpart->mapAbstractAttribute)
        this->mapAttribute.insert(std::pair<std::string*, &Attribute>(t.first, t.second)); //TODO: COPY t.second
    this->draw = rootpart->draw;
}*/

cAbstractCircPart::cAbstractCircPart()       { this->type = ePartType::PartType_Circ; }
cAbstractComputePart::cAbstractComputePart() { this->type = ePartType::PartType_Zip;  }

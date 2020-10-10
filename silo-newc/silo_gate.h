#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_GATE_HEAD
#define SILO_GATE_HEAD

#include "silo_node.h"

SIGNAL NodeReadInput(NODE * node, PORTID portid);
#define NodeRdIn NodeReadInput

void GateADD(NODE * node);
void GateSUB(NODE * node);
void GateMUL(NODE * node);
void GateDIV(NODE * node);
void GateMUL(NODE * node);
void GateAND(NODE * node);
void GateIOR(NODE * node);
void GateEOR(NODE * node);

void GateROL(NODE * node);
void GateROR(NODE * node);


#endif

#ifdef __cplusplus
}
#endif
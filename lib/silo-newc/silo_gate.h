#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_GATE_HEAD
#define SILO_GATE_HEAD

#include "silo_node.h"

SIGNAL NodeReadInput(NODE * node, PORTID portid);
#define NodeRdIn NodeReadInput

void GateMeetWire(NODE * node);

void GateADD(NODE * node);
void GateSUB(NODE * node);
void GateMUL(NODE * node);
void GateDIV(NODE * node);
void GateMOD(NODE * node);
void GateAND(NODE * node);
void GateIOR(NODE * node);
void GateEOR(NODE * node);

void GateROL(NODE * node);
void GateROR(NODE * node);
/*
void GateMULS(NODE * node);
void GateDIVS(NODE * node);
void GateMODS(NODE * node);
void GateSAR(NODE * node);
void GateSHL(NODE * node);
void GateSHR(NODE * node);
*/

void GateMUX(NODE * node);


#endif

#ifdef __cplusplus
}
#endif

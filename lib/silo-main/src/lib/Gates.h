#ifndef SILO_STDLIB_GATES_H
#define SILO_STDLIB_GATES_H

void Gates_NOT_Gate(NODE *);
void Gates_Buffer(NODE *);
void Gates_AND_Gate(NODE *);
void Gates_IOR_Gate(NODE *);
void Gates_EOR_Gate(NODE *);
void Gates_NAND_Gate(NODE *);
void Gates_NIOR_Gate(NODE *);
void Gates_NEOR_Gate(NODE *);
void Gates_Controlled_Buffer(NODE *);
void Gates_Controlled_Inverter(NODE *);

#endif

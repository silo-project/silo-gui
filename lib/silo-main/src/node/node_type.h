/*
	Name: Node Configuration Module Header
	Copyright: SILO
	Author: rumium
	Date: 09-10-20 16:56 (DD-MM-YY)
	Description: configure node
*/
#ifndef SILO_NODECONF_H
#define SILO_NODECONF_H

int  NodeSetMemAttr(NODE *, DEFT_ADDR);
int  NodeSetMemData(NODE *, DEFT_ADDR);
int  NodeSetMemSent(NODE *, DEFT_ADDR);
int  NodeSetMemSend(NODE *, DEFT_ADDR);

DEFT_ADDR NodeGetMemAttr(NODE *);
DEFT_ADDR NodeGetMemData(NODE *);
DEFT_ADDR NodeGetMemSent(NODE *);
DEFT_ADDR NodeGetMemSend(NODE *);

void NodeSetType(NODE * node, void (*fn)(NODE*));
void NodeSetAttr(NODE * node, DEFT_WORD attr, DEFT_ADDR index);
// input is not able
// storage is not able
void NodeSetSend(NODE * node, PORTID port, struct silo_wire dest);








#endif

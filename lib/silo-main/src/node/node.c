#include "node_type.c"

#include <stdio.h>
#include <stdlib.h>
#include "../define.h"
#include "../node/node.h"
#include "../simulator/simulator.h"

typedef struct Simulator SIMU;

// initialization node management system
int NodeInit(SIMU * s) {
	s->node.size = BASICMEM;
	s->node.list = (NODE**)malloc(s->node.size);
	s->node.last = s->node.number = 0;

	if (s->node.list == NULL)
		return 1;
	return 0;
}
int NodeSysReset(SIMU * s) {
	NODEID i;

	for (i = 0; i < s->node.last; i++)
		NodeDelete(s->node.list[i]);
	s->node.size = BASICMEM;
	s->node.list = realloc(s->node.list, s->node.size);
	s->node.last = s->node.number = 0;

	if (s->node.list == NULL)
		return 1;
	return 0;
}

NODE * NodeCreate(SIMU * s) {
	NODE * p = (NODE*)malloc(sizeof(NODE));
	NODEID nodeid;

	if ((nodeid = NodeGetID(&s->node)) >= s->node.size/sizeof(NODE*)) {
	NODE ** q;

	s->node.size = s->node.last / (BASICMEM/sizeof(NODE*));
	s->node.size = s->node.last % (BASICMEM/sizeof(NODE*)) ? s->node.size+1 : s->node.size;
	s->node.size *= BASICMEM;

	q = (NODE**)realloc((void*)s->node.list, s->node.size);

	if (p == NULL || q == NULL)
		return NULL;
	s->node.list = q;
	}

	p->ndid = nodeid;
	p->func = NULL;
	p->simu = s;

	p->size.attr = 0;
	p->size.data = 0;
	p->size.sent = 0;
	p->size.send = 0;

	p->attr = malloc(0);
	p->data = malloc(0);
	p->sent = malloc(0);
	p->send = malloc(0);
    
	if (p->attr == NULL || p->data == NULL || p->sent == NULL || p->send == NULL) {
		if (p->attr == NULL)
			free(p->attr);
		if (p->data == NULL)
			free(p->data);
		if (p->sent == NULL)
			free(p->sent);
		if (p->send == NULL)
			free(p->send);
		free(p);
		if ((s->node.last == s->node.number) && (s->node.last > 0))
			s->node.last = --s->node.number;
		else
			s->node.number--;
		return NULL;
	}
	s->node.list[nodeid] = p;
	return p;
}
void NodeDelete(NODE * node) {
	struct SystemNode * n = &node->simu->node;

	free(node->attr);
	free(node->data);
	free(node->sent);
	free(node->send);
	n->list[node->ndid] = NULL;

	if (n->deleted) {
		if (n->recycle > node->ndid) {
			n->recycle = node->ndid;
		}
	}
	else {
		n->recycle = node->ndid;
		n->deleted = true;
	}

	free(node);
}
DEFT_ADDR NodeCreateMany(SIMU * simu, NODE ** buffer, DEFT_ADDR size) {
	DEFT_ADDR i;
	
	for (i = 0; i < size; i++)
		if ((buffer[i] = NodeCreate(simu)) == NULL)
			break;
	
	return i;
}
DEFT_ADDR NodeDeleteMany(NODE ** buffer, DEFT_ADDR size) {
	DEFT_ADDR i;
	
	for (i = 0; i < size; i++)
		NodeDelete(buffer[i]);
	
	return i;
}

NODE * NodeMakeCopy(NODE * p) { // duplication node
	DEFT_ADDR i;
	NODE * q = NodeCreate(p->simu);
	if (q == NULL)
		return NULL;

	if (NodeTypeCopy(q, p))
		return NULL;

	return q;
}
int NodeTypeCopy(NODE * d, NODE * s) {
	NODEID i;

	NodeSetType(d, s->func);
	
	NodeSetMemAttr(d, s->size.data);
	NodeSetMemSent(d, s->size.sent);
	NodeSetMemSend(d, s->size.send);
    
	for (i = 0; i < s->size.attr; i++)
		d->attr[i] = s->attr[i];
	for (i = 0; i < s->size.sent; i++)
		d->sent[i] = s->sent[i];
	for (i = 0; i < s->size.send; i++)
		d->send[i] = s->send[i];

	return 0;
}
int NodeDataCopy(NODE * d, NODE * s) {
	NODEID i;

	NodeSetMemData(d, s->size.attr);
	for (i = 0; i < s->size.data; i++)
		d->data[i] = s->data[i];
}

int NodeMoveSimu(SIMU * simu, NODE * node) {
	NODE * p = NodeCreate(simu);
	if ((p = NodeCreate(simu)) == NULL)
		return 1;
	NodeTypeCopy(p, node);
	p->simu = node->simu;
	NodeDelete(node);
	return 0;
}

NODEID NodeGetID(struct SystemNode * node) {
	NODEID i, j;
    
	if (node->deleted) {
		i = node->recycle;
		for (j = 0; node->list[j] != NULL && j < node->number; j++)
			;
		if (node->list[j] != NULL) {
			node->deleted = false;
		}
		node->recycle = j;
		return i;
	}
	else
	return node->last++;
}
void NodeSetID(struct SystemNode * node, NODEID nodeid) {
	if (node->deleted && node->recycle > nodeid)
		node->recycle = nodeid;
	else {
		node->recycle = -1;
		node->deleted = false;
	}
}
bool NodeCheckID(struct SystemNode * node, NODEID nodeid) { return node->list[nodeid]->func != NULL; }


NODEID NodeGetNumber(struct SystemNode * n) { return n->number; }
NODEID NodeGetLastID(struct SystemNode * n) { return n->last;   }
inline NODE * NodeGetPtr(struct SystemNode * n, NODEID nodeid) { return n->list[nodeid]; }

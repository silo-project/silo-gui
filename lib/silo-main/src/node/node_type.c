/*
	Name: Node Configuration Module
	Copyright: SILO
	Author: see AUTHOR file
	Date: 09-10-20 16:59 (DD-MM-YY)
	Description: configure node structures
*/
#include <stdio.h>
#include <stdlib.h>
#include "../define.h"
#include "../node/node.h"
#include "../node/node_type.h"

// how much using a memory?
int NodeSetMemAttr(NODE *node, DEFT_ADDR size) {
    void *p = realloc(node->attr, sizeof(DEFT_WORD) * size);

    if (p == NULL)
        return 1;
    node->attr = p;
    node->size.attr = size;
    return 0;
}

int NodeSetMemData(NODE *node, DEFT_ADDR size) {
    void *p = realloc(node->data, sizeof(VALUE) * size);

    if (p == NULL)
        return 1;
    node->data = p;
    node->size.data = size;
    return 0;
}

int NodeSetMemSent(NODE *node, DEFT_ADDR size) {
    void *p = realloc(node->sent, sizeof(SIGNAL) * size);

    if (p == NULL)
        return 1;
    node->sent = p;
    node->size.sent = size;
    return 0;
}

int NodeSetMemSend(NODE *node, DEFT_ADDR size) {
    void *p = realloc(node->send, sizeof(SENDFORM) * size);

    if (p == NULL)
        return 1;
    node->send = p;
    node->size.send = size;
    return 0;
}

DEFT_ADDR NodeGetMemAttr(NODE *node) { return node->size.attr; }

DEFT_ADDR NodeGetMemStrg(NODE *node) { return node->size.data; }

DEFT_ADDR NodeGetMemSent(NODE *node) { return node->size.sent; }

DEFT_ADDR NodeGetMemSend(NODE *node) { return node->size.send; }

// node configuration
void NodeSetType(NODE *node, void (*func)(NODE *)) {
    node->func = func;
}

void NodeSetAttr(NODE *node, DEFT_WORD attr, DEFT_ADDR offset) {
    node->attr[offset] = attr;
}

void NodeSetSend(NODE *node, PORTID portid, WIRE dst) {
    node->send[portid] = dst;
}

// node configuration array type
void NodeSetAttrs(NODE *node, const DEFT_WORD *attr, DEFT_ADDR maxlen) {
    DEFT_ADDR i;

    for (i = 0; i < maxlen; i++)
        node->attr[i] = attr[i];
    return;
}

void NodeSetSends(NODE *node, WIRE* target, DEFT_ADDR maxlen) {
    DEFT_ADDR i;

    for (i = 0; i < maxlen; i++)
        node->send[i] = target[i];
}



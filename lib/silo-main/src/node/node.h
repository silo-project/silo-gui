/*
	Name: silo node header
	Copyright: SILO
	Author: see AUTHORS file
	Date: 2020-10-04 18:17 (YYYY-MM-DD)
	Description: define node-structure, send-form
*/
#ifndef SILO_NODE_H
#define SILO_NODE_H

#include "../define.h"
#include "../wire.h"
#include "../signal.h"

// decl
typedef struct nodestruct NODE;
typedef struct sendformat SENDFORM;
typedef struct Simulator SIMU;

// defi
struct NodeMemorySize {
	DEFT_ADDR attr;
	DEFT_ADDR data;
	DEFT_ADDR sent; // srce = sent
	DEFT_ADDR send; // dest = send
};
struct SystemNode {
	NODE** list; // array of a node structure pointer
	DEFT_ADDR size; // size of node_list
	NODEID last;
	NODEID number; // valid nodes count
	NODEID recycle;
	bool   deleted;
};

typedef struct nodestruct {
	NODEID      ndid;
	SIMU      * simu;
	void     (* func)(NODE*);
	DEFT_WORD * attr;
	VALUE     * data;
	SIGNAL    * sent;
	WIRE      * send;
	struct NodeMemorySize size;
} NODE;
typedef struct sendformat {
	NODE * node;
	PORTID port;
} SENDFORM;



// functions
int NodeInit(SIMU *);
int NodeSysReset(SIMU *);

NODE * NodeCreate(SIMU *);
void   NodeDelete(NODE *);

// create or delete as many node
DEFT_ADDR NodeCreateMany(SIMU * simu, NODE ** buffer, DEFT_ADDR size);
DEFT_ADDR NodeDeleteMany(NODE ** buffer, DEFT_ADDR size);

NODE * NodeMakeCopy(NODE *);
int    NodeTypeCopy(NODE * dst, NODE * src);
int    NodeDataCopy(NODE * dst, NODE * src);
int    NodeMoveSimu(SIMU *, NODE *);





NODEID NodeGetID(struct SystemNode *); // get a usable(creatable) nodeid
void   NodeSetID(struct SystemNode *, NODEID); // return a nodeid no longer in use
bool   NodeCheckID(struct SystemNode *, NODEID);

NODEID NodeGetNumber(struct SystemNode *);
NODEID NodeGetLastID(struct SystemNode *);
NODE * NodeGetPtr(struct SystemNode *, NODEID);


#endif

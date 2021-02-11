/*
    Name : Logisim Default Libraries
    Description : implementation of Logisim dedicated libraries.
*/

#include "../node/node.h"
#include "../simulator/simulator.h"

void Gates_NOT_Gate(NODE * node) {
	SIGNAL i, o;
    
	i = node->sent[0];
	o.value =  SigGetSpeci(i);
	o.state =  SigGetSpeci(i);
	o.value = ~SigGetLogic(i);
	SimuTransfer(node->send[0], o);
}

void Gates_Buffer(NODE * node) {
	SIGNAL i, o;
    
	i = node->sent[0];
	o.value = SigGetSpeci(i);
	o.state = SigGetSpeci(i);
	o.value = SigGetLogic(i);
	SimuTransfer(node->send[0], o);
}

/*
void Gates_AND_Gate(NODE * node) {

// attr[0] = number of inputs
// attr[1] = negate

	SIGNAL x, y;
	DEFT_WORD inputs, negate, bitcnt, i;
    
	inputs = node->attr[0];
	negate = node->attr[1];
    
	for (i = 0, bitcnt = 1; i < inputs; i++, bitcnt <<= 1) {
		x.value = (negate & bitcnt) ? ~SigGetLogic(node->sent[i]) : node->sent[i].value;
		x.state = node->sent[i].state;
        
		x.value
	}
}

/*
void Gates_IOR_Gate(NODE *);
void Gates_EOR_Gate(NODE *);
void Gates_NAND_Gate(NODE *);
void Gates_NIOR_Gate(NODE *);
void Gates_NEOR_Gate(NODE *);
void Gates_Controlled_Buffer(NODE *);
void Gates_Controlled_Inverter(NODE *);

*/

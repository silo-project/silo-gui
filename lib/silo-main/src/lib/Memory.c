/*
    Name : Logisim Default Libraries
    Description : implementation of Logisim dedicated libraries.
*/

#include <stdio.h>

#include "../node/node.h"
#include "../lib/Memory.h"
#include "../simulator/simulator.h"

void Memory_Register(NODE * node) {
/*
attr[0] : type of edge
0 == rising edge
1 == falling edge
2 == high level
3 == low level
data[0] : PREV_CLK
data[1] : value
inpt[0] : CURR_CLK
inpt[1] : input
oupt[0] : output
*/
	int state = 0;
	SIGNAL s;
	s.state = -1;
	switch (node->attr[0]) {
	case 0:
		if (SigChkRiseEdge(&node->data[0], SigGetLogic(node->sent[0])))
			state = true;
		break;
	case 1:
		if (SigChkFallEdge(&node->data[0], SigGetLogic(node->sent[0])))
			state = true;
		break;
	case 2:
		if (SigGetLogic(node->sent[0]))
			state = true;
		break;
	case 3:
		if (!SigGetLogic(node->sent[0]))
			state = true;
		break;
	default:
		printf("Memory_Register : Invalid type of edge.\n");
	}
	if (state) {
		node->data[1] = (node->data[1] & ~node->sent[1].state) | node->sent[1].value;
		s.value = node->data[1];
		SimuTransfer(node->send[0], s);
	}
}

void Memory_Counter(NODE * node) {
/*
attr[0] : type of edge
0 == rising edge
1 == falling edge
2 == high level
3 == low level
data[0] : PREV_CLK
data[1] : value
inpt[0] : CURR_CLK
inpt[1] : input
inpt[2] : enable
inpt[3] : alternative
oupt[0] : output

*/
	SIGNAL s;
	s.state = -1;
	if (SigChkTypeEdge(&node->data[0], SigGetLogic(node->sent[0]), node->attr[0])) {
		if (SigGetLogic(node->sent[2])) {
			if (SigGetLogic(node->sent[3]))
				node->data[1]--;
			else
				node->data[1]++;
        	}
        	else if (SigGetLogic(node->sent[3]))
			node->data[1] = SigGetLogic(node->sent[1]);
	}
}

#include "../include/signal.h"
#include "../include/node/node.h"
#include "../include/gate/gate.h"
#include "../include/gate/Gates.h"
#include "../include/simulator/simulator.h"

void IO_PrintSignal(NODE * node) {
	SIGNAL s;
	NODEID i;
	s = node->sent[0];
	
	printf("PrintSignal : ");
    
	for (i = 0; i < 64; i++) {
		switch ((s.value & 1)<<1|(s.state & 1)) {
		case 0:
			putchar('X');
			break;
		case 1:
			putchar('0');
			break;
		case 2:
			putchar('E');
			break;
		case 3:
			putchar('1');
			break;
		default:
			putchar('?');
		}
		s.value >>= 1;
		s.state >>= 1;
	}
	putchar('\n');
}

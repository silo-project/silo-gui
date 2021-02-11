#include "../include/signal.h"
#include "../include/node/node.h"
#include "../include/lib/Gates.h"
#include "../include/simulator/simulator.h"

#include "../include/lib/Clock.h"

void Clock_clock(NODE * n) {
	SIGNAL s;
	
	s.state = -1;
	s.value = n->data[0] = !n->data[0];
	
	SimuTransfer(n->send[0], s);
}

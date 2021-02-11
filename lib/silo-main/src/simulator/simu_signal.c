#include <stdlib.h>

#include "../define.h"
#include "../wire.h"
#include "../node/node.h"
#include "../simulator/simulator.h"
#include "../simulator/thread.h"

void SimuSendSignal(SENDFORM dest, SIGNAL signal) { dest.node->sent[dest.port] = signal; }
void SimuWakeUpNode(NODE * node) { node->simu->simu.sentlist[node->ndid] = true; }

void SimuTransfer(WIRE wire, SIGNAL signal) {
	for (DEFT_WORD i = 0; i < wire.size; i++) {
		SimuSendSignal(wire.send[i], signal);
		SimuWakeUpNode(wire.send[i].node);
	}
}

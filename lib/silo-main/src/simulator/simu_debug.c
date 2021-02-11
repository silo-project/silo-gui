#include "../define.h"
#include "../signal.h"
#include "../node/node.h"
#include "../simulator/simulator.h"

void SimuResetNextExec(struct Simulator * s) {
	for (NODEID i = 0; i < NodeGetLastID(&s->node); i++)
		s->simu.nextexec[i] = NULL;
	s->simu.nextemax = 0;
}
void SimuResetSentList(struct Simulator * s) {
	for (NODEID i = 0; i < NodeGetLastID(&s->node); i++)
		s->simu.sentlist[i] = false;
}
void SimuListofNextExec(struct Simulator * s) {
	for (NODEID i = 0; i < NodeGetLastID(&s->node); i++)
		printf("NextExec(%lld) : %p\n", i, s->simu.nextexec[i]);
}
void SimuListofSentList(struct Simulator * s) {
	printf("SentList : ");

	for (NODEID i = 0; i < NodeGetLastID(&s->node); i++)
		printf("%d ", s->simu.sentlist[i]);
} 

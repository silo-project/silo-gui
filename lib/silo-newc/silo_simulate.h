#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_SIMULATE_HEAD
#define SILO_SIMULATE_HEAD

#include "silo_define.h"

int SimuInit(void);
int Simulate(void);

int SimuReSizeList();

void SimuSend(SENDFORM sendform, SIGNAL signal);
void SimuSendInteger(SENDFORM sendform, DEFT_WORD integer);
void SimuMakeList(void);

#endif

#ifdef __cplusplus
}
#endif

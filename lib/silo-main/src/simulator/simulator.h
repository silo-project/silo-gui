/*
	Name: silo simulator header for external
	Copyright: SILO
	Author: see AUTHORS file
	Date: 2020-12-28 09:02 (YYYY-MM-DD)
	Description: define simulator API, structure
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_SIMULATOR_H
#define SILO_SIMULATOR_H

#include "../define.h"
#include "../node/node.h"
#include "../signal.h"
#include "thread.h"

typedef struct signalstruct SIGNAL;
typedef struct Simulator SIMU;

struct SystemSimu {
    NODE **nextexec;
    NODEID nextemax;
    char *sentlist;
    bool needmake;
    pthread_cond_t *cond;
    pthread_mutex_t *mtx;
    pthread_cond_t *makecond;
    pthread_mutex_t *makemtx;
    pthread_attr_t *attr;
    struct SystemThread thread;
};

typedef struct Simulator {
    struct SystemNode node;
    struct SystemSimu simu;
} SIMU;


int SimuInit(void);

SIMU *SimuCreate(void);
int SimuDelete(SIMU *);

DEFT_WORD SimuCreateClock(SIMU *, NODE *);
void SimuDeleteClock(SIMU *, DEFT_WORD);

int SimuReSize(SIMU *);

void SimuSendSignal(SENDFORM, SIGNAL);
void SimuWakeUpNode(NODE *);
void SimuTransfer(WIRE, SIGNAL);

int Simulate(SIMU *);

void SimuResetNextExec(SIMU *);
void SimuResetSentList(SIMU *);
void SimuListofNextExec(SIMU *);
void SimuListofSentList(SIMU *);

NODEID SimuMakeList(SIMU *);

int SimuThreadSetNum(SIMU *, unsigned long long);
unsigned long long SimuThreadGetNum(struct SystemThread *);
void SimuTickMode(struct SystemThread *);
void SimuStepMode(struct SystemThread *);
bool SimuGetSimMode(struct SystemThread *);

#endif

#ifdef __cplusplus
};
#endif
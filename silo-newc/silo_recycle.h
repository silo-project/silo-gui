#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_RECYCLE_HEAD
#define SILO_RECYCLE_HEAD

#include "silo_define.h"


int RecyInit();
int RecyStatus(void);
int RecyAbleID();

void   RecyPush(NODEID nodeid);
NODEID RecyPull(void);

void RecySetgcOfs(NODEID nodeid);
void RecyStartgc(NODEID nodeid);



#endif

#ifdef __cplusplus
}
#endif
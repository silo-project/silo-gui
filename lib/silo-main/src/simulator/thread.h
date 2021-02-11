#ifndef SILO_THREAD_HEAD
#define SILO_THREAD_HEAD

#include <pthread.h>

typedef struct nodestruct NODE;
typedef struct Simulator SIMU;

static void SimuThreadTickEndHandler(SIMU * s);

struct ThreadArgument {
	DEFT_WORD workid;
	DEFT_WORD makemx;
	SIMU * simulator;
};

struct SystemThread {
	DEFT_WORD number;
	pthread_t ** tidptr;
	struct ThreadArgument ** argptr;
	DEFT_WORD endcount;
	DEFT_WORD stepcount;
	pthread_cond_t * cond;
	pthread_mutex_t * mtx;

	pthread_t   * tcontrol; // thread control
	pthread_cond_t * tcond;
	pthread_mutex_t * tmtx;
	bool status; // 0 == waiting, 1 == running
	bool mode; // 0 == tick mode, 1 == step mode
	DEFT_WORD maxres;
	
	NODE * clock;
	DEFT_WORD clmax;
    void *tickendhandler;
};

#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_SIGNAL_HEAD
#define SILO_SIGNAL_HEAD

#include "silo_define.h"


// define of signal
typedef SIGNALSIZE VALUE;
typedef SIGNALSIZE STATE;

typedef struct signalstruct SIGNAL;

typedef struct signalstruct {
	VALUE value;
	STATE state;
} SIGNAL;


#endif

#ifdef __cplusplus
}
#endif

#ifndef SILO_SIGNAL_HEAD
#define SILO_SIGNAL_HEAD

#include "define.h"


// define of signal
typedef SIGNALSIZE VALUE;
typedef SIGNALSIZE STATE;

typedef struct signalstruct SIGNAL;

typedef struct signalstruct {
	VALUE value;
	STATE state;
} SIGNAL;

VALUE SigGetFloat(SIGNAL);
VALUE SigGetError(SIGNAL);
VALUE SigGetLogic(SIGNAL);
VALUE SigGetSpeci(SIGNAL);

VALUE SigChkRiseEdge(VALUE * prev, VALUE curr);
VALUE SigChkFallEdge(VALUE * prev, VALUE curr);
VALUE SigChkTypeEdge(VALUE * prev, VALUE curr, VALUE type);
SIGNAL MeetWire(SIGNAL, SIGNAL);
SIGNAL PullUp(SIGNAL);
SIGNAL PullDown(SIGNAL);



#endif

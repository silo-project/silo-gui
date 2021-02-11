#include "define.h"
#include "signal.h"

VALUE SigGetFloat(SIGNAL signal) { return ~signal.value & ~signal.state; }
VALUE SigGetError(SIGNAL signal) { return  signal.value & ~signal.state; }
VALUE SigGetLogic(SIGNAL signal) { return  signal.value &  signal.state; }
VALUE SigGetSpeci(SIGNAL signal) { return ~signal.state; }

VALUE SigChkRiseEdge(VALUE * prev, VALUE curr) {
    if (!*prev && curr) // previous == 0 && current == 1
        return *prev = 1;
    *prev = 1;
    return 0;
}
VALUE SigChkFallEdge(VALUE * prev, VALUE curr) {
    if (!(!*prev && curr)) // prev == 1 && curr == 0
        return *prev = 0;
    *prev = 0;
    return 1;
}
VALUE SigChkTypeEdge(VALUE * prev, VALUE curr, VALUE type) {
    if (!type) {
        if (!*prev && curr)
            return *prev = 1;
    }
    else {
        if (*prev && !curr)
            *prev = 0;
    }
    return 1;
}

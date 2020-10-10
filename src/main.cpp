#include <cstdio>

#include "silo_define.h"
#include "silo_node.h"
#include "silo_nodeconf.h"
#include "silo_signal.h"
#include "silo_gate.h"
#include "silo_simulate.h"
#include "silo_recycle.h"

int main(int argc, char** argv) {
    NODEID a;
    SIGNAL a_ar, b_ar;
    SENDFORM a_sd, b_sd, c_sd, dst;
    NODE * node;

    NodeInit();
    RecyInit();
    SimuInit();

    a = NodeCreate();
    NodeSetType(a, GateDIV);
    NodeSetMemory(a, 32);
    NodeSetOfsInpt(a, 0);
    NodeSetOfsOupt(a, 4);

    node = NodeGetPtr(a);

    printf("Pointer(Input) : %p\n", node->input);
    printf("Pointer(Output) : %p\n", node->output);

    a_ar.value = 12;
    a_ar.state = -1;

    b_ar.value = 3;
    b_ar.state = -1;

    a_sd.nodeid = a;
    a_sd.portid = 0;

    b_sd.nodeid = a;
    b_sd.portid = 1;

    c_sd.nodeid = a;
    c_sd.portid = 2;

    dst.nodeid = a;
    dst.portid = 0;

    NodeSetOupt(dst, c_sd);

    SimuSend(a_sd, a_ar);
    SimuSend(b_sd, b_ar);

    SimuMakeList();
    Simulate();

    printf("Result : %d\n", node->input[2].value);

    return 0;
}
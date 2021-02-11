/*
	Name: SILO main
	Copyright: SILO Project
	Author: see AUTHOR file
	Date: 10-10-20 09:09 (DD-MM-YY)
	Description: SILO main function
*/
/*
The MIT License (MIT)

Copyright (c) 2020 SILO Project

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "define.h"
#include "signal.h"
#include "node/node.h"
#include "node/node_type.h"
#include "simulator/simulator.h"

int main(int argc, char ** argv) {
    int status = 0;
    struct Simulator * simulator = SimuCreate();
    if (simulator == NULL)
        return -1;
	status += NodeInit(simulator);
    
    if (status) {
        printf("failed to initialization\n");
        return -1;
    }
	
	NODEID thread_num;
    NODEID node_num;
    NODEID simu_num;
	
	printf("Input Thread Number : ");
    fflush(stdout);
	scanf("%lld", &thread_num);

	printf("Input Node Number : ");
    fflush(stdout);
	scanf("%lld", &node_num);
    
	printf("Input Simulate Number : ");
    fflush(stdout);
	scanf("%lld", &simu_num);
    

	
	NODEID i;
	SENDFORM s;
	SIGNAL signal;
	NODE * p;
	
	clock_t st, ed;
	

	signal.state = -1;
	signal.value = 0xb7;
    s.port = 0;
	

	if (SimuThreadSetNum(simulator, thread_num))
        printf("error\n");
    
	for (i = 0; i < node_num; i++) {
		p = NodeCreate(simulator);
        if (p == NULL)
            return 1;
		NodeSetType(p, GateBusyWait);
		NodeSetMemSrce(p, 1);
		NodeSetMemDest(p, 1);
		
		s.node = p;
		NodeSetDest(p, 0, s);
        
		printf("node created : %lld, pointer : %p\n", p->ndid, &p->ndid);
        fflush(stdout);
	}
    
    SimuReSize(simulator);
    
    for (i = 0; i < node_num; i++) {
        p = NodeGetPtr(&simulator->node, i);
        s.node = p;
        if (rand()%2)
            Transfer(s, signal);
    }
    
	printf("before simulate\n");
    fflush(stdout);
    
	st = clock();
    
	for (i = 0; i < simu_num; i++) {
        loop:
        status = Simulate(simulator);
        if (status) {
            goto loop;
        }
//        SimuListofNextExec();
		if (i / 1000 && (i % 1000 == 0)) {
            printf("Thousand End : %d\n", ((int) i) / 1000);
            fflush(stdout);
        }
	}
	printf("Simulate count : %d\n", (int)i);
    fflush(stdout);
	
	ed = clock();
	printf("Time : %.3f\n", (float)(ed - st)/CLOCKS_PER_SEC);
    fflush(stdout);
	
	return 0;
}


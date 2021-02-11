#include "../include/node/node_wire.h"

int WireAdd(WIRE * wire, PORTID * portid, SENDFORM sendform) {
	void * p = realloc(wire->send, sizeof(SENDFORM) * ++wire->size);
	if (p == NULL)
		return 1;
	wire->send = p;
	wire->send[*portid = wire->size-1] = sendform;
	
	return 0;
}
int WireDel(WIRE * wire, PORTID portid) {
	void * p;
	
	if (portid == wire->size-1)
		wire->size--;
	else if (portid < wire->size-1)
		wire->send[portid] = wire->send[--wire->size];
	else
		return 1;
	
	p = realloc(wire->send, sizeof(SENDFORM) * wire->size);
	
	if (p == NULL)
		return 1;
	wire->send = p;
	return
}

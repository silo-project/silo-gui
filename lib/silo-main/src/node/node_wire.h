#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_NODE_WIRE_H
#define SILO_NODE_WIRE_H

int WireAdd(WIRE *, PORTID *, SENDFORM);
int WireDel(WIRE *, PORTID);

#endif

#ifdef __cplusplus
};
#endif
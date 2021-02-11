/*
	Name: silo wire header
	Copyright: SILO
	Author: see AUTHORS file
	Date: 2020-12-28 09:00 (YYYY-MM-DD)
	Description: define wire structrure
*/
#ifndef SILO_WIRE_H
#define SILO_WIRE_H

typedef struct sendformat SENDFORM;

typedef struct silo_wire WIRE;

typedef struct silo_wire {
	SENDFORM * send;
	DEFT_WORD  size;
} WIRE;

#endif

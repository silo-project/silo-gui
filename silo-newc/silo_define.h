/*
	Name: SILO defines
	Copyright: SILO Project
	Author: rumium
	Date: 10-10-20 09:14
	Description: basic SILO defines
*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SILO_DEFINE_HEAD
#define SILO_DEFINE_HEAD

// default processing size
#define SILO_WORD int
#define SILO_ADDR long long

typedef unsigned SILO_WORD DEFT_WORD;
typedef unsigned SILO_ADDR DEFT_ADDR;

typedef DEFT_WORD SIGNALSIZE;
typedef DEFT_WORD NODEID;
typedef DEFT_WORD PORTID;

#define BASICMEM 4096 // 4KiB = 1Page

typedef union unisign {
	SILO_WORD uint;
	SILO_ADDR sint;
} UNISIGN;

#endif

#ifdef __cplusplus
}
#endif
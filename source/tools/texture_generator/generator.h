#ifndef _H_GENERATOR
#define _H_GENERATOR

#include "checker.h"
#include "noise.h"

#define START 0
#define CHECKER 0
#define NOISE 1
#define END 2

extern const char* supported_type[];
extern void (*Creator[])(int, char**);
extern int get_type(const char* type);

#endif
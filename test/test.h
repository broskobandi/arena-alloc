#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>

extern int num_tests;
extern int num_tests_passed;
extern int num_tests_failed;

#define ASSERT(expr)\
	if (!(expr)) {\
		printf("[TEST FAILED]: %s\n\tLine: %d\n\tFile %s\n", #expr, __LINE__, __FILE__);\
		num_tests_failed++;\
	} else {\
		num_tests_passed++;\
	}\
	num_tests++;

#endif

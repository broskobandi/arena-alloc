#include "../test.h"
#include "../test_init.h"

int num_tests = 0;
int num_tests_passed = 0;
int num_tests_failed = 0;

int main(void) {

	test_init();

	if (!num_tests_failed) {
		printf("\n[ALL %d TESTS PASSED]\n", num_tests);
	} else {
		printf("\n[%d TESTS PASSED]\n", num_tests_passed);
		printf("[%d TESTS FAILED]\n", num_tests_failed);
	}

	return 0;
}

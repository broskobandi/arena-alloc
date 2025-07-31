#include "test_mutex.h"
#include "test.h"

void test_mutex() {
	arena_traits_t traits = ARENA_TRAIT_THREADSAFE;
	handle_thread_lock(traits);
	ASSERT(pthread_mutex_trylock(&g_mutex));
	handle_thread_unlock(traits);
}

#include "common.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
arena_list_t g_arena_list;

void handle_thread_lock(arena_traits_t traits) {
	if (traits & ARENA_TRAIT_THREADSAFE)
		pthread_mutex_lock(&g_mutex);
}

void handle_thread_unlock(arena_traits_t traits) {
	if (traits & ARENA_TRAIT_THREADSAFE)
		pthread_mutex_unlock(&g_mutex);
}

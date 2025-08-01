#ifndef __ARENA_COMMON_H__
#define __ARENA_COMMON_H__

#include "arena_alloc.h"
#include <pthread.h>

#define ARENA_SIZE 1024LU
#define ARENA_LIST_INIT 0xCAFED00DLU

#ifndef MAX_NUM_ARENAS_PER_NODE_CUSTOM
#define MAX_NUM_ARENAS_PER_NODE 8
#else
#define MAX_NUM_ARENAS_PER_NODE MAX_NUM_ARENAS_PER_NODE_CUSTOM
#endif

extern pthread_mutex_t g_mutex;
void handle_thread_lock(arena_traits_t traits);
void handle_thread_unlock(arena_traits_t traits);

typedef struct storage storage_t;
struct storage {
	alignas(max_align_t) unsigned char buff[1024];
	storage_t *next;
	size_t offset;
};

struct arena {
	storage_t head;
	storage_t *tail;
	arena_traits_t traits;
};

typedef struct arena_node arena_node_t;
struct arena_node {
	arena_t arenas[MAX_NUM_ARENAS_PER_NODE];
	size_t num_arenas;
	arena_node_t *next;
};

typedef struct arena_list {
	arena_node_t head;
	arena_node_t *tail;
	size_t is_init;
} arena_list_t;

struct ptr {
	storage_t *storage;
	void *data;
	size_t size;
};

extern arena_list_t g_arena_list;

#endif

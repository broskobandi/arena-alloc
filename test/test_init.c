#include "test.h"
#include "test_init.h"

static inline void test_arena_init();
static inline void test_init_arena_list();
static inline void test_allocate_arena();
static inline void test_arena_list_new_node();

void test_init() {
	test_init_arena_list();
	test_allocate_arena();
	test_arena_list_new_node();
	test_arena_init();
}

static inline void test_init_arena_list() {
	arena_list_t list;
	init_arena_list(&list);
	ASSERT(list.is_init == ARENA_LIST_INIT);
	ASSERT(!list.head.num_arenas);
	ASSERT(!list.head.next);
}

static inline void test_allocate_arena() {
	arena_list_t list;
	init_arena_list(&list);

	arena_t *arena = NULL;
	allocate_arena(&list, &arena);
	ASSERT(arena);
}

static inline void test_arena_list_new_node() {
	arena_list_t list;
	init_arena_list(&list);
	arena_node_t *old_tail = list.tail;

	new_arena_node(&list);
	ASSERT(list.tail != old_tail);
	ASSERT(!list.tail->next);
	ASSERT(!list.tail->num_arenas);
}

static inline void test_arena_init() {
	arena_init(NULL, ARENA_TRAIT_NONE);
	ASSERT(g_arena_list.is_init != ARENA_LIST_INIT);

	arena_t *arenas[MAX_NUM_ARENAS_PER_NODE * 3] = {0};
	for (size_t i = 0; i < MAX_NUM_ARENAS_PER_NODE + 1; i++) {
		arena_init(&arenas[i], ARENA_TRAIT_USE_HEAP);
		if (arenas[i]) {
			ASSERT(arenas[i]->tail);
			ASSERT(!arenas[i]->tail->offset);
			ASSERT(!arenas[i]->tail->next);
		}
		if (i >= MAX_NUM_ARENAS_PER_NODE) {
			ASSERT(g_arena_list.tail->num_arenas == 1);
		} else {
			ASSERT(g_arena_list.tail->num_arenas == i + 1);
		}
	}

	arena_node_t *old_node = g_arena_list.tail;
	for (size_t i = 0; i < MAX_NUM_ARENAS_PER_NODE + 1; i++) {
		arena_init(&arenas[i], ARENA_TRAIT_NONE);
		if (arenas[i]) {
			ASSERT(arenas[i]->tail);
			ASSERT(!arenas[i]->tail->offset);
			ASSERT(!arenas[i]->tail->next);
		}
		if (i >= MAX_NUM_ARENAS_PER_NODE) {
			ASSERT(g_arena_list.tail == old_node);
		}
	}
}

#include "init.h"
#include <stdlib.h>

#include <stdio.h>

void arena_init(arena_t **arena, arena_traits_t traits) {
	if (!arena) return;
	*arena = NULL;
	handle_thread_lock(traits);

	if (g_arena_list.is_init != ARENA_LIST_INIT)
		init_arena_list(&g_arena_list);

	if (
		g_arena_list.tail->num_arenas + 1 > MAX_NUM_ARENAS_PER_NODE &&
		traits & ARENA_TRAIT_USE_HEAP
	)
		new_arena_node(&g_arena_list);

	allocate_arena(&g_arena_list, arena);
	if (*arena) init_arena(arena, traits);

	handle_thread_unlock(traits);
}

void init_arena_list(arena_list_t *list) {
	list->is_init = ARENA_LIST_INIT;
	list->tail = &list->head;
	list->head.num_arenas = 0;
	list->head.next = NULL;
}

void allocate_arena(arena_list_t *list, arena_t **arena) {
	if (list->tail->num_arenas + 1 <= MAX_NUM_ARENAS_PER_NODE) {
		*arena = &list->tail->arenas[list->tail->num_arenas];
		list->tail->num_arenas++;
	}
}

int new_arena_node(arena_list_t *list) {
	list->tail->next = malloc(sizeof(arena_list_t));
	if (!list->tail->next) return 1;
	list->tail->next->num_arenas = 0;
	list->tail->next->next = NULL;
	list->tail = list->tail->next;
	return 0;
}

void init_arena(arena_t **arena, arena_traits_t traits) {
	(*arena)->tail = &(*arena)->head;
	(*arena)->tail->next = NULL;
	(*arena)->tail->offset = 0;
	(*arena)->traits = traits;
}

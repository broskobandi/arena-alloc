#ifndef __ARENA_INIT_H__
#define __ARENA_INIT_H__

#include "common.h"

void init_arena_list(arena_list_t *list);
int new_arena_node(arena_list_t *list);
void allocate_arena(arena_list_t *list, arena_t **arena);
void init_arena(arena_t **arena, arena_traits_t traits);

#endif

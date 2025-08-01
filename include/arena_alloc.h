#ifndef __ARENA_ALLOC_PUBLIC_HEADER_H__
#define __ARENA_ALLOC_PUBLIC_HEADER_H__

#include <stddef.h>
#include <stdalign.h>

typedef struct arena arena_t;
typedef struct ptr ptr_t;

typedef enum arena_traits {
	ARENA_TRAIT_NONE = 1 << 0,
	ARENA_TRAIT_THREADSAFE = 1 << 1,
	ARENA_TRAIT_USE_HEAP = 1 << 2
} arena_traits_t;

/* First parameter must not be NULL. If 'arena' is still NULL after
 * calling this function, try passing ARENA_TRAIT_THREADSAFE. If it still fails,
 * try recompiling the library with -DMAX_NUM_ARENAS_PER_NODE_CUSTOM=[value],
 * where value is greater than the default 8. If it still fails, your system is
 * probably out of memory. */
void arena_init(arena_t **arena, arena_traits_t traits);

/* First parameter must not be NULL. 'alignment' must be a power of 2 and not 0.
 * 'size' must not be 0. */
ptr_t *arena_alloc(arena_t *arena, size_t alignment, size_t size);

/*  */
void arena_free(ptr_t **ptr);

/**/
void arena_reset(arena_t *arena);

/**/
void arena_destroy(arena_t **arena);

#endif

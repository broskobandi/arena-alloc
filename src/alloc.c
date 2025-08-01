#include "alloc.h"

ptr_t *arena_alloc(arena_t *arena, size_t alignment, size_t size) {
	if (!arena || !alignment || !size || (alignment & (alignment - 1)))
		return NULL;
	ptr_t *ptr = NULL;
	return ptr;
}

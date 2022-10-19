#include "stack.h"

#include <stdlib.h>



stack_t stack_init(size_t start_size, size_t el_size, uint8_t grow_mode) {
	return (stack_t) {
		.stack = malloc(start_size * el_size),
		.index = 0,
		.size = start_size
	};
}
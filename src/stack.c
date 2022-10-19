#include "stack.h"

#include <stdlib.h>
#include <string.h>



size_t __stack_push(stack_t *stack, void *data) {
	if (stack->index == stack->size) {
		switch (stack->__grow_mode) {
			case GROW_LEAST: stack->stack = realloc(stack->stack, (++stack->size) * stack->__el_size); break;
			case GROW_FIXED2: stack->stack = realloc(stack->stack, (stack->size <<= 1) * stack->__el_size); break;
		}
	}

	memcpy(stack->stack + stack->index * stack->__el_size, data, stack->__el_size);

	return stack->index++;
}

void *__stack_pop(stack_t *stack) {
	return stack->stack + (--stack->index) * stack->__el_size;
}



stack_t __stack_init(size_t start_n, size_t el_size, uint8_t grow_mode) {
	size_t size = start_n * el_size;

	return (stack_t) {
		.stack = malloc(size),
		.index = 0,
		.size = size,

		.__el_size = el_size,
		.__grow_mode = grow_mode
	};
}

void stack_free(stack_t stack) {
	free(stack.stack);
}
#pragma once



#ifndef __STACK_H
#define __STACK_H

#define stack_push(stack, X)						__stack_push(stack, (void*) &(X))
#define stack_pop(stack)							__stack_pop(stack)

#define stack_init(start_n, mode, TYPE)				__stack_init(start_n, sizeof(TYPE), mode)
#define stack_free(stack)							__stack_free(stack)

#include "commons.h"



enum { //if we want to push but we dont have enough space: (index == size)
	GROW_LEAST, //grow one slot
	GROW_FIXED2 //double the size (to use this, make sure start_size is at least > 0 (0 * 2 = 0, so no gain in that case))
};



typedef struct {
	void *stack;
	size_t index;
	size_t size;

	size_t __el_size;
	uint8_t __grow_mode;
} stack_t;



size_t __stack_push(stack_t *stack, void *data);
void *__stack_pop(stack_t *stack);

stack_t __stack_init(size_t start_n, size_t el_size, uint8_t grow_mode);
void __stack_free(stack_t stack);



#endif
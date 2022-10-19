#pragma once



#ifndef __STACK_H
#define __STACK_H

#include "commons.h"



enum { //if we want to push but we dont have enough space: (index == size)
	GROW_LEAST, //grow one slot
	GROW_FIXED2 //double the size (to use this, make sure start_size is at least > 0 (0 * 2 = 0, so no gain in that case))
};



typedef struct {
	void *stack;
	size_t index;
	size_t size;
} stack_t;



stack_t stack_init(size_t start_size, size_t el_size, uint8_t grow_mode);



#endif
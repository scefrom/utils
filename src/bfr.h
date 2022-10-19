#pragma once

#ifndef __BFR_H
#define __BFR_H

#include "commons.h"



#define BFR_NULL						((bfr_t) {.bfr = NULL .index = 0, .size = 0})

#define BFR_FROM_CONST(C)				((bfr_t) {.bfr = (uint8_t*) (C), .index = 0, .size = sizeof(C)})
#define BFR_FROM_CONST_NO_NULL(C)		((bfr_t) {.bfr = (uint8_t*) (C), .index = 0, .size = sizeof(C) - 1})

#define BFR_FROM_STR(S)					((bfr_t) {.bfr = (uint8_t*) (S), .index = 0, .size = strlen(S) + 1})
#define BFR_FROM_STR_NO_NULL(S)			((bfr_t) {.bfr = (uint8_t*) (S), .index = 0, .size = strlen(S)})

#define BFR_GET_STR(B, I)				((char*) ((B).bfr + (I)))



typedef struct {
	uint8_t *bfr;
	size_t index;
	size_t size;
} bfr_t;



bfr_t bfr_from_fstr(uint8_t null, const char *format, ...);

size_t bfr_write(bfr_t *bfr, bfr_t abfr);
size_t bfr_append(bfr_t *bfr, bfr_t abfr);

bfr_t bfr_init(uint8_t *bfr, size_t size);
void bfr_free(bfr_t bfr);

#endif
#include "bfr.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>



bfr_t* bfr_from_fstr(uint8_t null, const char *format, ...) {
	va_list alist, blist;
	va_start(alist, format);
	va_copy(blist, alist);

	size_t s = vsnprintf(NULL, 0, format, alist) + 1;
	char *bfr = malloc(s * sizeof(char));

	vsprintf(bfr, format, blist);

	if (null) bfr[s - 1] = 0;

	va_end(alist);
	va_end(blist);

	return bfr_init((uint8_t*) bfr, s - (!null));
}



size_t bfr_write(bfr_t *bfr, bfr_t abfr) {
	size_t s = abfr.size - abfr.index;
	if (bfr->index + s > bfr->size)
		bfr->bfr = realloc(bfr->bfr, (bfr->size = bfr->index + s) * sizeof(uint8_t));

	size_t i = bfr->index;

	while (abfr.index < abfr.size) {
		bfr->bfr[bfr->index++] = abfr.bfr[abfr.index++];
	}

	return i;
}

size_t bfr_append(bfr_t *bfr, bfr_t abfr) {
	size_t s = abfr.size - abfr.index;
	bfr->bfr = realloc(bfr->bfr, (bfr->size + s) * sizeof(uint8_t));

	size_t i = bfr->index;

	for (int64_t ii = ((int64_t) bfr->size) - 1; ii >= ((int64_t) i); ii--)
		bfr->bfr[ii + s] = bfr->bfr[ii];

	bfr->size += s;

	while (abfr.index < abfr.size)
		bfr->bfr[bfr->index++] = abfr.bfr[abfr.index++];

	return i;
}



bfr_t* bfr_init(uint8_t *src, size_t size) {
	bfr_t *bfr = malloc(sizeof(bfr_t));
	bfr->bfr = src;
	bfr->index = size;
	bfr->size = size;

	return bfr;
}

void bfr_free(bfr_t *bfr) {
	free(bfr->bfr);
	free(bfr);
}
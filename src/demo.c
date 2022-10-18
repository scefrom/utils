#include "commons.h"
#include "bfr.h"
#include "file.h"

#include <stdio.h>



int main(int argc, char **argv) {
	if (argc > 1) {
		bfr_t *file_buffer = file_read_tfile(argv[1]);

		printf("file_buffer:\n\n%s\n", (char*) file_buffer->bfr);
	}
}
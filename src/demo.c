#include "commons.h"
#include "bfr.h"
#include "file.h"
#include "stack.h"

#include <stdio.h>



int main(int argc, char **argv) {
	//stack demo:
	stack_t stack = stack_init(4, size_t, STACK_GROW_LEAST);

	size_t x = 10;
	stack_push(stack, x);
	stack_push(stack, x);
	stack_push(stack, x);
	stack_push(stack, x);
	stack_push(stack, x);

	for (size_t i = 0; i < stack.index; i++) {
		printf("element: %d\n", stack_fetch(stack, i));
	}

	printf("\nsize: %ld\n", stack.size);

	stack_free(stack);

	//file demo:
	/*if (argc > 1) {
		bfr_t file_buffer;
		
		if (file_read_file(&file_buffer, argv[1])) {
			printf("file_buffer:\n\n%s\n", (char*) file_buffer.bfr);
		} else {
			printf("error occurred\n");
		}
	}*/

	return 0;
}
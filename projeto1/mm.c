#include <stdio.h>
#include <stdlib.h>

void *xmalloc(size_t size) {
	register void *value = malloc(size);
	if (value == 0) {
		perror("Virtual memory exhausted");
		exit(-1);
	}
	return value;
}

void *xrealloc(void *ptr, size_t size) {
	register void *value = realloc(ptr, size);
	if (value == 0) {
		perror("Virtual memory exhausted");
		exit(-1);
	}
	return value;
}

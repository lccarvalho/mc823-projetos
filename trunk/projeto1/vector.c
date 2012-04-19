#include"vector.h"
#include <stdio.h>
#include"mm.h"
#include <stdlib.h>
#include <string.h>

int vector_free_size(vector vec) {
	return vec->max_size - vec->cur;
}

vector vector_initialize(int count, int size_of_elt, void (*rem_func)(void*)) {
	vector vec = NULL;
	vec = (vector) xmalloc(sizeof (struct vec));
	vec->cur = 0;
	vec->rem_func = rem_func;
	vec->free_elt_on_remove_elt = 1;

	vec->max_size = count > 0 ? count : 0;
	vec->elt_size = size_of_elt > 0 ? size_of_elt : 0;

	if (vec->max_size > 0 && size_of_elt > 0) {
		vec->elts = malloc(count * size_of_elt);
		if (vec->elts == NULL) {
			fprintf(stderr, "Out of memory");
			exit(-1);
		}
	} else
		vec->elts = NULL;

	return vec;
}

int vector_add_element(vector vec, void *elt) {
	if (vector_free_size(vec) <= 0) {
		if (vec->max_size == 0)
			vec->max_size = 1;

		vec->elts = xrealloc(vec->elts, (2 * vec->max_size * sizeof (void*)));
		vec->max_size *= 2;
	}

	vec->elts[vec->cur] = malloc(vec->elt_size);
	memcpy(vec->elts[vec->cur], elt, vec->elt_size);
	vec->cur++;


	return 0;
}

void* vector_get_element_at(vector vec, int pos) {
	if (pos >= 0 && pos < vec->cur)
		return vec->elts[pos];
	return NULL;
}

int vector_remove_element_at(vector vec, int pos) {
	int i;

	if (pos >= 0 && pos < vec->cur) {
		if (vec->rem_func != NULL)
			vec->rem_func(vec->elts[pos]);

		for (i = pos; i < vec->cur - 1; i++)
			vec->elts[i] = vec->elts[i + 1];

		vec->cur--;

		return 0;
	}

	return -1;

}

int vector_free(vector vec) {
	if (vec == NULL)
		return 0;
	//reverse because removes faster
	while (vec->cur > 0)
		vector_remove_element_at(vec, vec->cur - 1);

	free(vec->elts);
	free(vec);
	return 0;
}

int vector_contains(vector vec, void *elt,int (*cmp_func)(void*,void*)) {
	int i;
	if (vec != NULL) {
		for (i = 0; i < vec->cur; i++) {
			
			if (cmp_func(vector_get_element_at(vec,i),elt))
				return 1;
		}
	}
	return 0;
}
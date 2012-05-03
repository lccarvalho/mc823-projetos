#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que aloca memória.
 *
 * @Param size - tamanho a ser alocado
 *
 * @Returns   inteiro representando sucesso ou fracasso
 */
/* ----------------------------------------------------------------------------*/
void *xmalloc(size_t size) {
	register void *value = malloc(size);
	if (value == 0) {
		perror("Virtual memory exhausted");
		exit(-1);
	}
	return value;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar usada para realocar memória
 *
 * @Param ptr - ponteiro para a estrutura a ser realocada
 * @Param size - tamanho a ser realocado
 *
 * @Returns   inteiro representando sucesso ou fracasso
 */
/* ----------------------------------------------------------------------------*/
void *xrealloc(void *ptr, size_t size) {
	register void *value = realloc(ptr, size);
	if (value == 0) {
		perror("Virtual memory exhausted");
		exit(-1);
	}
	return value;
}

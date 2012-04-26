#include "mm.h"
#include "str.h"

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que inicializa uma estrututura do tipo string.
 *
 * @Param size - tamanho da string a ser inicializada
 *
 * @Returns   string inicializada
 */
/* ----------------------------------------------------------------------------*/
string str_initialize(size_t size) {
	string str;
	str = (string) xmalloc(sizeof (struct str));
	str->cur = 0;
	str->max = size;

	if (size != 0) {
		str->s = (char*) xmalloc((size + 1) * sizeof (char));
		str->s[0] = '\0';
	} else str->s = NULL;

	return str;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que libera a memória alocada por uma string
 *
 * @Param str - estrutura do tipo string
 *
 * @Returns um inteiro descrevendo o sucesso ou falha
 */
/* ----------------------------------------------------------------------------*/
int str_free(string str) {
	if (str == NULL)
		return 0;

	if (str->s != NULL) {
		free(str->s);
	}
	free(str);
	return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que indica o tamanho máximo da estrutura do tipo string.
 *
 * @Param str - estrutura do tipo string
 *
 * @Returns   inteiro descrevendo o tamanho máximo da string.
 */
/* ----------------------------------------------------------------------------*/
size_t str_max_size(string str) {
	return str->max;
}


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que indica o tamanho atual da estrutura do tipod string.
 *
 * @Param str - estrutura do tipo string
 *
 * @Returns   inteiro representando o tamanho atual da string.
 */
/* ----------------------------------------------------------------------------*/
size_t str_cur_size(string str) {
	return str->cur;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que mostra quanto há de espaço livre na estrutura de dados
 * do tipo string.
 *
 * @Param str - estrutura do tipo string
 *
 * @Returns   inteiro representando quanto há de espaço livre
 */
/* ----------------------------------------------------------------------------*/
size_t str_free_size(string str) {
	return str_max_size(str) - str_cur_size(str);
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que concatena uma string 'padrão' com uma estrutura
 * do tipo string
 *
 * @Param to - estrutura do tipo string
 * @Param from - string
 * @Param num - tamanho da string a ser concatenada
 *
 * @Returns   inteiro indicando sucesso ou fracasso.
 */
/* ----------------------------------------------------------------------------*/
int str_concat_chararr(string to, char *from, size_t num) {
	if (from == NULL)
		return 0;

	if (str_free_size(to) < num) {
		int newmaxsize = 2 * str_max_size(to) + num + 1;
		to->s = (char*) xrealloc(to->s, newmaxsize);
		to->max = newmaxsize;

	}

	strncat(to->s, from, num * sizeof(char));
	to->cur += num;
	to->s[to->cur] = '\0';

	return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que concatena duas estruturas do tipo string.
 *
 * @Param to - estrutura do tipo string a receber a concatenação
 * @Param from - estrutura do tipo string a ser concatenada
 *
 * @Returns   inteiro indicando sucesso ou fracasso
 */
/* ----------------------------------------------------------------------------*/
int str_concat_str(string to, string from) {
	return str_concat_chararr(to, from->s, from->cur);
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que compara uma estrutura do tipo string com uma string 
 * "padrao".
 *
 * @Param str - estrutura do tipo string
 * @Param elt - string
 * @Param size - tamanho da string
 *
 * @Returns     inteiro indicando sucesso ou fracasso
 */
/* ----------------------------------------------------------------------------*/
int str_cmp_str_chararr(string str, char *elt, size_t size) {
	if (((string) str)->cur != size)
		return 0;
	return memcpy(((string) str)->s, elt, ((string) str)->cur * sizeof (char));
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * Função auxiliar que compara duas estruturas do tipo string.
 *
 * @Param str1 - estrutura do tipo string
 * @Param str2 - estrutura do tipo string
 *
 * @Returns   inteiro indicando sucesso ou fracasso
 */
/* ----------------------------------------------------------------------------*/
int str_cmp_str_str(string str1, string str2){
	//the arguments must be in the order below
	return str_cmp_str_chararr(str1,str2->s,str2->cur);
}

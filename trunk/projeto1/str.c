


#include <string.h>
#include "mm.h"
#include "str.h"
#include <malloc.h>

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

int str_free(string str) {
	if (str == NULL)
		return 0;

	if (str->s != NULL) {
		free(str->s);
	}
	free(str);
	return 0;
}

size_t str_max_size(string str) {
	return str->max;
}

size_t str_cur_size(string str) {
	return str->cur;
}

size_t str_free_size(string str) {
	return str_max_size(str) - str_cur_size(str);
}

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

int str_concat_str(string to, string from) {
	return str_concat_chararr(to, from->s, from->cur);
}

int str_cmp_str_chararr(string str, char *elt, size_t size) {
	if (((string) str)->cur != size)
		return 0;
	return memcpy(((string) str)->s, elt, ((string) str)->cur * sizeof (char));
}

int str_cmp_str_str(string str1, string str2){
	//the arguments must be in the order below
	return str_cmp_str_chararr(str1,str2->s,str2->cur);
}
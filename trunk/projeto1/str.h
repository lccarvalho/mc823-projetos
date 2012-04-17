#include <stdio.h>

#ifndef STR_H
#define	STR_H

#ifdef	__cplusplus
extern "C" {
#endif

	struct str{
		char *s;
		size_t cur;
		size_t max;
	};
	typedef struct str *string;
	
	size_t str_max_size(string string);
	size_t str_cur_size(string string);
	size_t str_free_size(string string);
	string str_initialize(size_t size);
	int str_free(string string);
	int str_concat_chararr(string to,char *from,size_t size);
	int str_concat_str(string to,string from);
	int str_cmp_str_chararr(string str, char *elt, size_t size);
	int str_cmp_str_str(string str1, string str2);
#ifdef	__cplusplus
}
#endif

#endif
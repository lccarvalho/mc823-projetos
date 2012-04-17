#ifndef VECTOR_H
#define	VECTOR_H

#ifdef	__cplusplus
extern "C" {
#endif

	typedef struct vec{
		void **elts;
		int cur;
		int max_size;
		int elt_size;
		int free_elt_on_remove_elt;
		void (*rem_func)(void*);
	}vec;
	
	typedef vec *vector; 
	
	int vector_free_size(vector vec);
	
	vector vector_initialize(int count, int size_of_elt,void (*rem_func)(void*));
	int vector_add_element(vector vec,void *elt);
	void* vector_get_element_at(vector vec,int pos);
	int vector_remove_element_at(vector vec,int pos);
	int vector_free(vector vec);
	int vector_contains(vector vec,void *elt,int (*cmp_func)(void *,void*));
#ifdef	__cplusplus
}
#endif

#endif	/* VECTOR_H */


/* 
 * File:   mm.h
 * Author: root
 *
 * Created on March 5, 2012, 2:39 PM
 */


#include<stdlib.h>
#ifndef MM_H
#define	MM_H

#ifdef	__cplusplus
extern "C" {
#endif
	void *xmalloc(size_t size);
	void *xrealloc(void *ptr, size_t newsize);


#ifdef	__cplusplus
}
#endif

#endif	/* MM_H */


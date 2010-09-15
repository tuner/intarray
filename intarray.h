/*
  +----------------------------------------------------------------------+
  | author: kari lavikka <kari.lavikka@dynamoid.com>                     |
  +----------------------------------------------------------------------+

  $Id: intarray.h,v 1.4 2009/03/30 10:36:24 phadej Exp $
*/

#ifndef _INTARRAY_H
#define _INTARRAY_H 1

#include <sys/types.h>
#include <stdint.h>

#define INTARRAY_NOT_FOUND -1

#define INTARRAY_DATA(x) ((int32_t *)Z_STRVAL_P(x))
#define INTARRAY_LENGTH(x) (Z_STRLEN_P(x) / sizeof(int32_t))

int    intarray_check(zval *var_array, int index);
int    intarray_binarysearch(int32_t array[], size_t length, int32_t value);
size_t intarray_intersect(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]);
size_t intarray_union(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]);
size_t intarray_difference(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]);
size_t intarray_symmetric_difference(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]);
int    intarray_binarysearch_slot(int32_t a[],size_t al,int32_t value);

#endif /* _INTARRAY_H */

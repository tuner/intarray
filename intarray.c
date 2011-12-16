/*
 * Copyright (c) 2007-2009 Sulake Dynamoid Oy
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * - Neither the name of the 'intarray' nor the names of its contributors may
 *   be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  $Id: intarray.c,v 1.17 2009/10/16 11:25:56 tuner Exp $
 */

#include <string.h>
#include <stdbool.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/standard/php_rand.h"
#include "ext/standard/php_smart_str.h"
#include "intarray.h"
#include "php_intarray.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

/* {{{ intarray_functions[]
 *
 * Every user visible function must have an entry in intarray_functions[].
 */
zend_function_entry intarray_functions[] = {
	PHP_FE(intarray_create, NULL)
	PHP_FE(intarray_create_from_array, NULL)
	PHP_FE(intarray_get, NULL)
	PHP_FE(intarray_set, NULL)
	PHP_FE(intarray_insert, NULL)
	PHP_FE(intarray_delete, NULL)
	PHP_FE(intarray_length, NULL)
	PHP_FE(intarray_search, NULL)
	PHP_FE(intarray_binarysearch_slot, NULL)
	PHP_FE(intarray_binarysearch, NULL)
	PHP_FE(intarray_intersect, NULL)
	PHP_FE(intarray_sort, NULL)
	PHP_FE(intarray_dump, NULL)
	PHP_FE(intarray_to_json, NULL)
	PHP_FE(intarray_union, NULL)
	PHP_FE(intarray_difference,NULL)
	PHP_FE(intarray_symmetric_difference, NULL)
	PHP_FE(intarray_add, NULL)
	PHP_FE(intarray_slice, NULL)
	PHP_FE(intarray_shuffle, NULL)
	PHP_FE(intarray_check, NULL)
	PHP_FE(intarray_subset, NULL)
	{NULL, NULL, NULL}	/* Must be the last line in intarray_functions[] */
};
/* }}} */
/* {{{ intarray_module_entry
 */
zend_module_entry intarray_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"intarray",
	intarray_functions,
	PHP_MINIT(intarray),
	PHP_MSHUTDOWN(intarray),
	NULL,		/* Replace with NULL if there's nothing to do at request start */
	NULL,	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(intarray),
#if ZEND_MODULE_API_NO >= 20010901
	"1.0.0", /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */
/* {{{ COMPILE_DL_INTARRAY */
#ifdef COMPILE_DL_INTARRAY
ZEND_GET_MODULE(intarray)
#endif
/* }}} */
/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(intarray)
{
	return SUCCESS;
}
/* }}} */
/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(intarray)
{
	return SUCCESS;
}
/* }}} */
/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(intarray)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "intarray support", "enabled");
	php_info_print_table_row(2, "intarray version", "$Id: intarray.c,v 1.17 2009/10/16 11:25:56 tuner Exp $");
	php_info_print_table_end();
}
/* }}} */
/* {{{ intarray_binarysearch */
/**
 * Binary search to sorted int32 array. 
 *
 * @param array Haystack
 * @param length Size of the array
 * @param value The needle
 * @return Index of needle or NOT_FOUND
 */
int intarray_binarysearch(int32_t array[], size_t length, int32_t value) {
	int left, right, mid;

	left = 0;
	right = length - 1;

	while (left <= right) {
		mid = (left + right) / 2;

		if (array[mid] == value) return mid;

		if (value < array[mid]) {
			right = mid - 1;
		} else if (value > array[mid]) {
			left = mid + 1;
		}
	}

	return INTARRAY_NOT_FOUND;
}
/* }}} */
/* {{{ intarray_intersect */
/**
 * Creates an intersection of two sorted arrays.
 *
 * @param a Array
 * @param al Length of the array
 * @param b Another array
 * @param bl Length of another array
 * @param result Pointer to resulting array. Must be at least as big as the smaller source array.
 * @return Length of the resulting array.
 */ 
size_t intarray_intersect(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]) {
	unsigned int ap, bp, rp;

	ap = bp = rp = 0;

	if (al == 0 || bl == 0) return 0;
	
	do {
		if (a[ap] == b[bp]) {
			result[rp++] = a[ap];
			ap++;
			bp++;

		} else if (a[ap] < b[bp]) {
			ap++;
		} else {
			bp++;
		}

	} while (ap < al && bp < bl);

	return rp;
}
/* }}} */
/* {{{ intarray_union */
/**
 * Creates a union of two sorted arrays.
 *
 * @param a Array
 * @param al Length of the array
 * @param b Another array
 * @param bl Length of another array
 * @param result Pointer to resulting array. Must be big enough to accommodate both source arrays.
 * @return Length of the resulting array.
 */ 
size_t intarray_union(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]) {
	unsigned int ap, bp, rp;

	ap = bp = rp = 0;

	if (al == 0 || bl == 0) return 0;

	do {
		if (a[ap] == b[bp]) {
			result[rp++] = a[ap];
			ap++;
			bp++;

		} else if (a[ap] < b[bp]) {
			result[rp++] = a[ap];
			ap++;
		} else {
			result[rp++] = b[bp];		
			bp++;
		}

	} while (ap < al && bp < bl);

	if (ap < al || bp < bl) {
		if(bp < bl) {
			do { 
				result[rp++] = b[bp];
				bp++;
			} while (bp < bl);
		} else {
			do {
				result[rp++] = a[ap];
				ap++;
			} while (ap < al);
		}
	}
	return rp;
}
/* }}} */
/* {{{ intarray_difference */
/**
 * Creates a difference of two sorted arrays.
 *
 * @param a Array
 * @param al Length of the array
 * @param b Array to subtract
 * @param bl Length of another array
 * @param result Pointer to resulting array. Must be as big as the original array.
 * @return Length of the resulting array.
 */ 
size_t intarray_difference(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]) {
	unsigned int ap, bp, rp;
	ap = bp = rp = 0;
	if (al == 0) return 0;

	if (bl == 0) {
		memcpy(result, a, al * sizeof(int32_t));
	}

	do {
		if (a[ap] == b[bp]) {
			ap++;
			bp++;
		} else if (a[ap] < b[bp]) {
			result[rp++] = a[ap];
			ap++;
		} else {
			bp++;
		}
	} while (ap < al && bp < bl);

	if (ap < al) {
		do {
			result[rp++] = a[ap];
			ap++;
		} while (ap < al);
	}
	return rp;
}
/* }}} */
/* {{{ intarray_symmetric_difference */
/**
 * Creates a symmetric difference (xor) of two arrays.
 *
 * @param a Array
 * @param al Length of the array
 * @param b Another array
 * @param bl Length of another array
 * @param result Pointer to resulting array. Must be big enough to accommodate both source arrays.
 * @return Length of the resulting array.
 */ 
size_t intarray_symmetric_difference(int32_t a[], size_t al, int32_t b[], size_t bl, int32_t result[]) {
	int32_t *union_tmp, *intersect_tmp;
	size_t union_length, intersect_length, result_length;

	/* trivial cases */
	if (al == 0 && bl == 0) {
		return 0;
	} else if (al == 0) {
		memcpy(result, b, bl * sizeof(int32_t));
		return bl;
	} else if (bl == 0) {
		memcpy(result, a, al * sizeof(int32_t));
		return al;
	}

	/* union */
	union_length = al + bl;
	union_tmp = emalloc(union_length * sizeof(int32_t));

	union_length = intarray_union(a, al, b, bl, union_tmp);

	/* union == al + bl => intersect == { } => xor == union */
	if (union_length == al + bl) {
		memcpy(result, union_tmp, union_length * sizeof(int32_t));
		efree(union_tmp);
		return union_length;
	}

	/* intersect */
	intersect_length = MIN(al, bl);
	intersect_tmp = emalloc(intersect_length * sizeof(int32_t));

	intersect_length = intarray_intersect(a, al, b, bl, intersect_tmp);

	/* result */
	result_length = intarray_difference(union_tmp, union_length, intersect_tmp, intersect_length, result);

	efree(union_tmp);
	efree(intersect_tmp);

	return result_length;
}
/* }}} */
/* {{{ intarray_binarysearch_slot */
/**
 * Binary search to sorted int32 array. Returns a slot for the needle. 
 *
 * @param array Haystack
 * @param length Size of the array
 * @param value The needle
 * @return Index of the slot for needle
 */
int intarray_binarysearch_slot(int32_t array[], size_t length, int32_t value) {
	int left, right, mid;
	left = 0;
	right = length -1;

	if (length < 1) {
		return -1;
	}

	while (left <= right) {
		mid = (left + right) / 2;

		if(value == array[mid]) {
			return -1;
		} else if (mid > 0 && array[mid-1] < value && value < array[mid]) {
			return mid;
		} else if (value > array[mid]) {
			left = mid + 1;
		} else if(value < array[mid]) {
			right = mid - 1;
		}
	}
	return left;
}
/* }}} */
/* {{{ intarray_check */
/**
 * Validates a String ZVAL as an intarray
 *
 * @param var_array Pointer to ZVAL
 * @param index Index for optional boundary check. Use -1 to omit.
 * @return SUCCESS if the string could be an intarray, FAILURE elsewhere
 */
inline int intarray_check(zval *var_array, int index) {
	size_t len;

	if (!var_array) {
		zend_error(E_WARNING, "Trying to access null array!");
		return FAILURE;
	}

	if (Z_TYPE_P(var_array) != IS_STRING) {
		zend_error(E_WARNING, "Doesn't seem to be an intarray, not a binarystring!");
		return FAILURE;
	}

	len = Z_STRLEN_P(var_array);

	/* valid intarray must be multiple of int32_t */
	if (len % sizeof(int32_t) != 0) {
		zend_error(E_WARNING, "Doesn't seem to be an intarray, weird length!");
		return FAILURE;
	}

	if (index != -1 && index >= (unsigned int)len / sizeof(int32_t)) {
		zend_error(E_WARNING, "Intarray index out of bounds!");
		return FAILURE;
	}

	return SUCCESS;
}
/* }}} */
/* {{{ proto boolean intarray_check(string intarray, [index = -1])
   Checks is given string is an intarray. Optional index to check is
   a certain index is valid. -1 index omits index check.
*/
PHP_FUNCTION(intarray_check) {
	size_t len;
	long index = -1;
	zval *var_array = NULL;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|l", &var_array, &index) == FAILURE) {
		RETURN_FALSE;
	}

	if (index < -1) {
		zend_error(E_WARNING, "Erroneous intarray index: %ld!", index);
		RETURN_FALSE;
	}

	if (!var_array) {
		/* Trying to access null array! */
		RETURN_FALSE;
	}

	if (Z_TYPE_P(var_array) != IS_STRING) {
		/* Doesn't seem to be an intarray, not a binarystring! */
		RETURN_FALSE;
	}

	len = Z_STRLEN_P(var_array);

	/* valid intarray must be multiple of int32_t */
	if (len % sizeof(int32_t) != 0) {
		/* Doesn't seem to be an intarray, weird length! */
		RETURN_FALSE;
	}

	if (index != -1 && index >= (unsigned)len / sizeof(int32_t)) {
		/* Intarray index out of bounds! */
		RETURN_FALSE;
	}

	RETURN_TRUE;
}
/* }}} */
/* {{{ int32_t_cmp */
static int int32_t_cmp (const void *a, const void *b) {
	const int32_t *da = (const int32_t *) a;
	const int32_t *db = (const int32_t *) b;

	return (*da > *db) - (*da < *db);
}
/* }}} */
/* {{{ proto string intarray_create(int length)
   Creates an intarray filled with zeroes. */
PHP_FUNCTION(intarray_create) {
	int32_t *array;
	long length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &length) == FAILURE) {
		RETURN_EMPTY_STRING();
	}

	if (length < 0) {
		zend_error(E_WARNING, "Trying to create an intarray of size %ld < 0!", length);
		RETURN_FALSE;
	}

	if (length == 0) {
		RETURN_EMPTY_STRING();
	}
	
	array = ecalloc((size_t)length + 1, sizeof(*array));
	RETURN_STRINGL((char *)array, sizeof(int32_t) * (size_t)length, 0);
}
/* }}} */
/* {{{ proto string intarray_create_from_array(array array)
   Converts contents of a php array to intarray. */
PHP_FUNCTION(intarray_create_from_array) {
	zval *src;
	HashTable *hash;
	HashPosition pos;
	uint32_t num;
	zval **data;
	
	int32_t *tmp_array;
	int32_t *dst_array;
	
	int32_t last;
	
	uint32_t i = 0;
	uint32_t j = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &src) == FAILURE) {
		RETURN_EMPTY_STRING();
	}

	hash = HASH_OF(src);
	num = zend_hash_num_elements(hash);

	if (num < 1) {
		RETURN_EMPTY_STRING();
	}
	
	tmp_array = (int32_t *) emalloc(sizeof(int32_t) * (size_t) num);
	dst_array = (int32_t *) emalloc(sizeof(int32_t) * (size_t) num);
	
	zend_hash_internal_pointer_reset_ex(hash, &pos);
	while (zend_hash_get_current_data_ex(hash, (void **) &data, &pos) == SUCCESS) {
		convert_to_long_ex(data);
		
		/* TODO: check if value out of int32_t bounds? */
		tmp_array[i++] = (int32_t) Z_LVAL_PP(data);
		zend_hash_move_forward_ex(hash, &pos);
	}
	
	/* sort */
	qsort(tmp_array, num, sizeof(int32_t), int32_t_cmp); 

	/* uniq */
	dst_array[0] = tmp_array[0];
	j = 1;
	last = dst_array[0];
	for (i = 1; i < num; i++) {
		if (tmp_array[i] != last) {
			dst_array[j++] = tmp_array[i];
			last = tmp_array[i];
		}
	}
	
	num = j;
	efree(tmp_array);
	dst_array = (int32_t *) erealloc(dst_array, sizeof(int32_t) * ((size_t) num + 1));
	dst_array[num] = 0;
	
	RETURN_STRINGL((char *) dst_array, sizeof(int32_t) * (size_t) num, 0);
}
/* }}} */
/* {{{ proto string intarray_sort(string intarray [, bool uniq = false])
   Returns a sorted version of an intarray. Removes duplicates if "uniq" is true.
   You can use this function to turn a random array to a valid "set" for
   operations like binary search, intersect, union, etc... */
PHP_FUNCTION(intarray_sort) {
	zval *var_array;
	zend_bool uniq = 0; 

	int32_t *src_array;
	int32_t *tmp_array;
	int32_t *dst_array;

	unsigned int i;
	unsigned int j;
	int32_t last;

	size_t num;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|b", &var_array, &uniq) == FAILURE) {
		RETURN_FALSE;
	}

	src_array = INTARRAY_DATA(var_array);
	num = INTARRAY_LENGTH(var_array);

	if (num == 0) {
		RETURN_EMPTY_STRING();
	}

	tmp_array = (int32_t *) emalloc(sizeof(int32_t) * ((size_t) num + 1));

	memcpy(tmp_array, src_array, sizeof(int32_t) * (size_t) num);
	tmp_array[num] = 0;
	qsort(tmp_array, num, sizeof(int32_t), int32_t_cmp); 
	
	if (!uniq) {
		RETURN_STRINGL((char *) tmp_array, sizeof(int32_t) * (size_t) num, 0);
	} else {
		dst_array = (int32_t *) emalloc(sizeof(int32_t) * (size_t) num);

		dst_array[0] = tmp_array[0];
		j = 1;
		last = dst_array[0];
		for (i = 1; i < num; i++) {
			if (tmp_array[i] != last) {
				dst_array[j++] = tmp_array[i];
				last = tmp_array[i];
			}
		}
		
		num = j;
		efree(tmp_array);
		dst_array = (int32_t *) erealloc(dst_array, sizeof(int32_t) * ((size_t) num + 1));
		dst_array[num] = 0;
		
		RETURN_STRINGL((char *) dst_array, sizeof(int32_t) * (size_t) num, 0);	
	}
}
/* }}} */
/* {{{ proto void intarray_insert(string intarray, int index, int value [, bool expand = true])
   Inserts a value to intarray at "index". Rest of the array is shifted and
   array is expanded if "expand" is true. Otherwise the last value is dropped. */
PHP_FUNCTION(intarray_insert) {
	zval *var_array;
	long index, value;
	zend_bool expand = 1; 

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll|b", &var_array, &index, &value, &expand) == FAILURE) {
		RETURN_FALSE;
	}

	/* Checking that index is in bounds and given intarray is valid
	   Index cannot be negative and can only be one above last index if
	   array is expanding. */
	if (index < 0 || intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	} else if (index > INTARRAY_LENGTH(var_array) - 1 && !expand) {
		RETURN_FALSE;
	} else if (index > INTARRAY_LENGTH(var_array)) {
		/* the index can only be one larger than the last index in the array */
		RETURN_FALSE;
	}
	
	if (expand) {
		Z_STRVAL_P(var_array) = erealloc(Z_STRVAL_P(var_array), Z_STRLEN_P(var_array) + sizeof(int32_t) + 1);
		Z_STRLEN_P(var_array) += sizeof(int32_t); 
		Z_STRVAL_P(var_array)[Z_STRLEN_P(var_array)] = 0;
	}
	
	/* Jos lis‰t‰‰n keskelle, pit‰‰ loppuja siirt‰‰ */
	if (index < Z_STRLEN_P(var_array)) {
		int32_t *ptr = ((int32_t *)Z_STRVAL_P(var_array)) + index;
		memmove(ptr + 1, ptr, Z_STRLEN_P(var_array) - index * sizeof(int32_t) - sizeof(int32_t));
	}
	
	((int32_t *)Z_STRVAL_P(var_array))[index] = value;
	
	RETURN_TRUE;
}
/* }}} */
/* {{{ proto void intarray_add(string intarray, int value)
   Adds a value to sorted intarray. Returns the index of newly added value
   or -1 if it was already present. */
PHP_FUNCTION(intarray_add) {
	zval *var_array;
	int index;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &var_array, &value) == FAILURE) {
		RETURN_FALSE;
	}

	/* checking intarray */
	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* Ok so an empty intarray isnt actualy a null pointer nor free'd, it is sizeof(int32_t) with Z_STRLEN_P set to 0,
	 * so if we give the index of 0. the array will be expanded to 0 + sizeof(int32_t) which is correct. */
	if (INTARRAY_LENGTH(var_array) == 0) {
		index = 0;
	} else {
		index = intarray_binarysearch_slot(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), value);
	}

	if (index >= 0) {
		Z_STRVAL_P(var_array) = erealloc(Z_STRVAL_P(var_array), Z_STRLEN_P(var_array) + sizeof(int32_t) + 1);
		Z_STRLEN_P(var_array) += sizeof(int32_t);
		Z_STRVAL_P(var_array)[Z_STRLEN_P(var_array)] = 0;

		if (index < Z_STRLEN_P(var_array)) {
			int32_t *ptr = ((int32_t *)Z_STRVAL_P(var_array)) + index;
			memmove(ptr + 1, ptr, Z_STRLEN_P(var_array) - index * sizeof(int32_t) - sizeof(int32_t));
		}

		((int32_t *)Z_STRVAL_P(var_array))[index] = value;
		RETURN_LONG(index);
	}

	RETURN_LONG(INTARRAY_NOT_FOUND);
}
/* }}} */
/* {{{ proto string intarray_subset(string intarray, int min, int max)
   Returns a subset of a sorted intarray. Min and max parameters define set boundaries (inclusive).
*/
PHP_FUNCTION(intarray_subset) {
	zval *var_array;
	long boundary_min, boundary_max;
	long index_min, index_max;

	int32_t *src_array;
	size_t src_length;
	int32_t *subset_array;
	size_t subset_length;

	/* TODO: accept NULL or FALSE as undefined and replace. */
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll", &var_array, &boundary_min, &boundary_max) == FAILURE) {
		RETURN_FALSE;
	}

	/* checking intarray */
	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* check sensible boundaries */
	if (boundary_max < boundary_min) {
		zend_error(E_WARNING, "Insensible boundaries. Max < min.");
		RETURN_FALSE;
	}

	src_array = INTARRAY_DATA(var_array);
	src_length = INTARRAY_LENGTH(var_array);

	/* check for empty source */
	if (src_length <= 0) {
		RETURN_EMPTY_STRING();
	}

	/* binarysearch_slot return -1 if exact match is found */
	index_min = intarray_binarysearch_slot(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), boundary_min);
	if (index_min == -1) {
		index_min = intarray_binarysearch(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), boundary_min);
	}

	index_max = intarray_binarysearch_slot(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), boundary_max);
	if (index_max == -1) {
		index_max = intarray_binarysearch(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), boundary_max);
		index_max++; /* boundaries are inclusive */
	}


//	zend_error(E_NOTICE, "min: %d, max: %d", (int)index_min, (int)index_max);

	/* If subset upper boundary does not reach lower boundary of source set */
	if (index_max <= 0 && src_array[0] != (int32_t)boundary_max) {
		RETURN_EMPTY_STRING();
	}

	if (index_min >= src_length) {
		RETURN_EMPTY_STRING();
	}

	subset_length = index_max - index_min;
	subset_array = (int32_t *)emalloc(sizeof(int32_t) * ((size_t) subset_length + 1));
	memcpy(subset_array, src_array + index_min, subset_length * sizeof(int32_t));
	subset_array[subset_length] = 0; /* terminate with null(s) */

	RETURN_STRINGL((char *)subset_array, subset_length * sizeof(int32_t), 0);
}
/* }}} */
/* {{{ proto integer intarray_delete(string array, int index [, bool contract = true])
   Deletes an item at "index" from intarray. If "contract" is true the array
   is contracted, otherwise a trailing zero is set. Returns the deleted value. */
PHP_FUNCTION(intarray_delete) {
	zval *var_array;
	long value, index;
	zend_bool contract = 1;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl|b", &var_array, &index, &contract) == FAILURE) {
		RETURN_FALSE;
	}

	if (index < 0 || intarray_check(var_array, index) == FAILURE) {
		RETURN_FALSE;
	}

	/* empty */
	if (INTARRAY_LENGTH(var_array) == 0) {
		zend_error(E_WARNING, "Attempted to delete from an empty intarray");
		RETURN_FALSE;
	}

	/* just one element */
	if (INTARRAY_LENGTH(var_array) == 1) {
		value = INTARRAY_DATA(var_array)[index];
		INTARRAY_DATA(var_array)[index] = 0;
		Z_STRLEN_P(var_array) = 0;
		RETURN_LONG(value);
	}
	
	value = INTARRAY_DATA(var_array)[index];
	
	/* Jos poistetaan keskelt‰, pit‰‰ loppuja siirt‰‰ */
	if (index < INTARRAY_LENGTH(var_array) - 1) {
		int32_t *ptr = INTARRAY_DATA(var_array) + index;
		memmove(ptr, ptr + 1, Z_STRLEN_P(var_array) - index * sizeof(int32_t) - sizeof(int32_t));
	}

	if (contract) {
		Z_STRVAL_P(var_array) = erealloc(Z_STRVAL_P(var_array), Z_STRLEN_P(var_array) - sizeof(int32_t) + 1);
		Z_STRLEN_P(var_array) -= sizeof(int32_t); 
		Z_STRVAL_P(var_array)[Z_STRLEN_P(var_array)] = 0;
	} else {
		INTARRAY_DATA(var_array)[INTARRAY_LENGTH(var_array) - 1] = 0;
	}		
	
	RETURN_LONG(value);
}
/* }}} */
/* {{{ proto void intarray_set(string intarray, int index, int value)
   Sets "value" to "index". */
PHP_FUNCTION(intarray_set) {
	zval *var_array;
	long value,index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zll", &var_array, &index, &value) == FAILURE) {
		RETURN_FALSE;
	}

	if (index < 0 || intarray_check(var_array, index) == FAILURE) {
		RETURN_FALSE;
	}

	if (INTARRAY_LENGTH(var_array) == 0) {
		zend_error(E_WARNING, "attempting to set a value in an empty intarray");
		RETURN_FALSE;
	}

	INTARRAY_DATA(var_array)[index] = (int32_t)value;

	RETURN_TRUE;
}
/* }}} */
/* {{{ proto int intarray_get(string intarray, int index)
   Returns value at "index". */
PHP_FUNCTION(intarray_get) {
	int32_t *array;
	zval *var_array;
	long index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &var_array, &index) == FAILURE) {
		RETURN_FALSE;
	}

	if (index < 0 ||
		intarray_check(var_array, index) == FAILURE ||
		INTARRAY_LENGTH(var_array) == 0) {
		RETURN_FALSE;
	}

	array = INTARRAY_DATA(var_array);

	RETURN_LONG((long)array[index]);
}
/* }}} */
/* {{{ proto string intarray_slice(string intarray, int offset [, int length])
   Returns a new intarray of (length) from (offset). */
PHP_FUNCTION(intarray_slice) {
	zval *var_array;

	int32_t *src_array;
	int32_t *tmp_array;
	long offset, length;
	size_t num;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl|l", &var_array, &offset, &length) == FAILURE) {
		RETURN_FALSE;
	}

	src_array = INTARRAY_DATA(var_array);
	num = INTARRAY_LENGTH(var_array);

	/* No lenght, take everything. */
	if (ZEND_NUM_ARGS() == 2) {
		length = num;
	}

	/* Fix the offset to be in the array */
	/* Offset larger than size of array */
	if (offset > (long) num) {
		RETURN_EMPTY_STRING();
	} else if (offset < 0 && ((long)num + offset) < 0) { 
		/* offset negative, size+offset negative */
		offset = 0;
	} else if (offset < 0 && ((long)num + offset) >= 0) {
		offset = (long)num + offset;
	}

	if (length < 0) { 
		length = (long)num - offset + length;
	} else if ((offset + length) > num) {
		length = (long)num - offset;
	}

	/* 0 elements to return or index out of bounds */
	if (length <= 0 || intarray_check(var_array, offset) == FAILURE) {
		RETURN_EMPTY_STRING();
	}

	tmp_array = (int32_t *) emalloc(sizeof(int32_t) * ((size_t) length + 1));
	memcpy(tmp_array, src_array + offset, length * sizeof(int32_t));
	tmp_array[length] = 0;

	RETURN_STRINGL((char *) tmp_array, sizeof(int32_t) * (size_t) length, 0);
}
/* }}} */
/* {{{ proto int intarray_length(string intarray)
   Returns length (items) of an intarray. */
PHP_FUNCTION(intarray_length) {
	zval *var_array;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &var_array) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	RETURN_LONG((long)INTARRAY_LENGTH(var_array));
}
/* }}} */
/* {{{ proto string intarray_shuffle(string intarray)
   Returns a randomly shuffled version of an intarray. */
PHP_FUNCTION(intarray_shuffle) {
	zval *var_array;
	int32_t *result;
	int32_t tmp;
	int n;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &var_array) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	if (INTARRAY_LENGTH(var_array) == 0) {
		RETURN_EMPTY_STRING();
	}

	result = (int32_t *)emalloc(sizeof(int32_t) * ((size_t)INTARRAY_LENGTH(var_array) + 1));
	memcpy(result, INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array) * sizeof(int32_t));
	result[INTARRAY_LENGTH(var_array)] = 0;

	for (n = 0; n < INTARRAY_LENGTH(var_array); n++) {
		int swap_index = php_rand(TSRMLS_C);
		RAND_RANGE(swap_index, 0, INTARRAY_LENGTH(var_array) - 1, PHP_RAND_MAX);
		tmp = result[swap_index];
		result[swap_index] = result[n];
		result[n] = tmp;
	}

	RETURN_STRINGL((char *)result, sizeof(int32_t) * (size_t)INTARRAY_LENGTH(var_array), 0);
}
/* }}} */
/* {{{ proto int intarray_binarysearch_slot(string intarray, int needle)
   Performs a binary search on a sorted intarray. Returns an index where
   value is or where value should be if not found. */
PHP_FUNCTION(intarray_binarysearch_slot) {
	zval *var_array;
	long value;
	int index;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &var_array, &value) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1)) {
		RETURN_FALSE;
	}

	index = intarray_binarysearch_slot(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), (int32_t)value);

	/* if key is already found, then search the real index */
	if (index < 0) {
		index = intarray_binarysearch(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), (int32_t)value);
	}

	if (index < 0) {
		index = 0;
	}

	RETURN_LONG(index);
}
/* }}} */
/* {{{ proto int intarray_binarysearch(string intarray, int needle)
   Performs a binary search on a sorted intarray. Returns an index or
   -1 if value was not found. */
PHP_FUNCTION(intarray_binarysearch) {
	zval *var_array;
	long value;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl", &var_array, &value) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* You ain't going to find anything in an empty intarray. */
	if (INTARRAY_LENGTH(var_array) == 0) { 
		RETURN_LONG(INTARRAY_NOT_FOUND); 
	}
	
	RETURN_LONG(intarray_binarysearch(INTARRAY_DATA(var_array), INTARRAY_LENGTH(var_array), (int32_t)value));
}
/* }}} */
/* {{{ proto int intarray_search(string intarray, int needle)
   Performs a linear search on intarray. Returns and index or -1 if value
   was not found. */
PHP_FUNCTION(intarray_search) {
	zval *var_array;
	long value;
	long start = 0;

	int32_t *array;
	size_t len;
	int n;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zl|l", &var_array, &value, &start) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* Nothing to be found in an empty array. */
	if (INTARRAY_LENGTH(var_array) == 0) {
		RETURN_LONG(INTARRAY_NOT_FOUND);
	}

	len = INTARRAY_LENGTH(var_array);
	array = INTARRAY_DATA(var_array);

	/* if start is negative start from len-start eleeent */
	if (start < 0) {
		start = len + start;
	}

	/* if start still < 0 (-start > len) return NOT_FOUND */
	if (start < 0) {
		RETURN_LONG(INTARRAY_NOT_FOUND);
	}
	
	for (n = start; n < len; n++) {
		if (array[n] == (int32_t)value) RETURN_LONG(n);
	}
	
	RETURN_LONG(INTARRAY_NOT_FOUND);
}
/* }}} */
/* {{{ proto string intarray_intersect(string intarray_a, string intarray_b)
   Returns an intersection of two sorted intarrays. */
PHP_FUNCTION(intarray_intersect) {
	zval *var_array_a, *var_array_b;
	int32_t *result;
	size_t result_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &var_array_a, &var_array_b) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array_a, -1) == FAILURE || intarray_check(var_array_b, -1) == FAILURE) {
		RETURN_FALSE;
	}

	if (INTARRAY_LENGTH(var_array_a) == 0 || INTARRAY_LENGTH(var_array_b) == 0) {
		RETURN_EMPTY_STRING();
	}

	result_length = MIN(INTARRAY_LENGTH(var_array_a), INTARRAY_LENGTH(var_array_b));
	result = emalloc((result_length + 1) * sizeof(int32_t));
	result[result_length] = 0;

	result_length = intarray_intersect(INTARRAY_DATA(var_array_a), INTARRAY_LENGTH(var_array_a),
			INTARRAY_DATA(var_array_b), INTARRAY_LENGTH(var_array_b), result);

	if (result_length > 0) {
		result = erealloc(result, (result_length + 1) * sizeof(int32_t));
		result[result_length] = 0;
	} else {
		efree(result);
		result = NULL;
		RETURN_EMPTY_STRING();
	}

	RETURN_STRINGL((char *)result, sizeof(int32_t) * (size_t)result_length, 0);
}
/* }}} */
/* {{{ proto string intarray_union(string intarray_a, string intarray_b)
   Returns a union of two sorted intarrays */
PHP_FUNCTION(intarray_union) {
	zval *var_array_a, *var_array_b;
	int32_t *result;
	size_t result_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &var_array_a, &var_array_b) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array_a, -1) == FAILURE || intarray_check(var_array_b, -1) == FAILURE) {
		RETURN_FALSE;
	}

	if (INTARRAY_LENGTH(var_array_a) == 0 && INTARRAY_LENGTH(var_array_b) != 0) {
		RETURN_ZVAL(var_array_b, 1, 0);
	} else if (INTARRAY_LENGTH(var_array_b) == 0 && INTARRAY_LENGTH(var_array_a) != 0) {
		RETURN_ZVAL(var_array_a, 1, 0);
	}

	/* Maximum size it could have */
	result_length = INTARRAY_LENGTH(var_array_a) + INTARRAY_LENGTH(var_array_b);
	result = emalloc((result_length + 1) * sizeof(int32_t));
	result[result_length] = 0;

	result_length = intarray_union(INTARRAY_DATA(var_array_a), INTARRAY_LENGTH(var_array_a),
			INTARRAY_DATA(var_array_b), INTARRAY_LENGTH(var_array_b), result);

	if (result_length > 0) {
		result = erealloc(result, (result_length + 1) * sizeof(int32_t));
		result[result_length] = 0;
	} else {
		efree(result);
		result = NULL;
		RETURN_EMPTY_STRING();
	}

	RETURN_STRINGL((char *)result, sizeof(int32_t) * (size_t)result_length, 0);
}
/* }}} */
/* {{{ proto string intarray_difference(string intarray_a, string intarray_b)
   Returns a relative complement of two intarrays - elements present in
   array A but without elements in array B */
PHP_FUNCTION(intarray_difference) {
	zval *var_array_a, *var_array_b;
	int32_t *result;
	size_t result_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz", &var_array_a, &var_array_b) == FAILURE) {
		RETURN_FALSE;
	}

	/* check */
	if (intarray_check(var_array_a, -1) == FAILURE || intarray_check(var_array_b, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* trivial cases */
	if (INTARRAY_LENGTH(var_array_a) == 0) {
		RETURN_EMPTY_STRING();
	} else if (INTARRAY_LENGTH(var_array_b) == 0) {
		RETURN_ZVAL(var_array_a, 1, 0);
	}

	/* Maximum size it could have */
	result_length = INTARRAY_LENGTH(var_array_a);
	result = emalloc((result_length + 1) * sizeof(int32_t));
	result[result_length] = 0;

	result_length = intarray_difference(INTARRAY_DATA(var_array_a), INTARRAY_LENGTH(var_array_a), INTARRAY_DATA(var_array_b), INTARRAY_LENGTH(var_array_b), result);

	if (result_length > 0) {
		result = erealloc(result, (result_length + 1) * sizeof(int32_t));
		result[result_length] = 0;
	} else {
		efree(result);
		result = NULL;
		RETURN_EMPTY_STRING();
	}

	RETURN_STRINGL((char *)result, sizeof(int32_t) * (size_t)result_length, 0);
}
/* }}} */
/* {{{ proto string intarray_symmetric_difference(string intarray_a, string intarray_b)
   Returns a symmetric difference (XOR) of two sorted intarrays. See: http://en.wikipedia.org/wiki/Symmetric_difference */
PHP_FUNCTION(intarray_symmetric_difference) {
	zval *var_array_a, *var_array_b;
	int32_t *result;
	size_t result_length;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "zz",
		&var_array_a, &var_array_b) == FAILURE) {
		RETURN_FALSE;
	}

	/* check */
	if (intarray_check(var_array_a, -1) == FAILURE || intarray_check(var_array_b, -1) == FAILURE) {
		RETURN_FALSE;
	}

	/* if length of either param == 0 return other one */
	if (INTARRAY_LENGTH(var_array_a) == 0 && INTARRAY_LENGTH(var_array_b) != 0) {
		RETURN_ZVAL(var_array_b, 1, 0);
	} else if(INTARRAY_LENGTH(var_array_b) == 0 && INTARRAY_LENGTH(var_array_a) != 0) {
		RETURN_ZVAL(var_array_a, 1, 0);
	}

	/* Result */
	result_length = INTARRAY_LENGTH(var_array_a) + INTARRAY_LENGTH(var_array_b);
	result = emalloc((result_length + 1) * sizeof(int32_t));
	result[result_length] = 0;

	result_length = intarray_symmetric_difference(INTARRAY_DATA(var_array_a), INTARRAY_LENGTH(var_array_a), INTARRAY_DATA(var_array_b), INTARRAY_LENGTH(var_array_b), result);
 	if (result_length > 0) {
		result = erealloc(result, (result_length + 1) * sizeof(int32_t));
		result[result_length] = 0;
	} else {
		efree(result);
		result = NULL;
		RETURN_EMPTY_STRING();
	}

	RETURN_STRINGL((char *)result, sizeof(int32_t) * result_length, 0);
}
/* }}} */
/* {{{ proto void intarray_dump(string intarray)
   Prints contents of an intarray */
PHP_FUNCTION(intarray_dump) {
	int32_t *array;
	zval *var_array;
	unsigned int n;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &var_array) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	array = INTARRAY_DATA(var_array);

	zend_printf("{");
	for (n = 0; n < INTARRAY_LENGTH(var_array); n++) {
		if (n > 0) zend_printf(",");
		zend_printf(" %d", array[n]);
	}
	zend_printf(" }");

	RETURN_TRUE;
}
/* }}} */
/* {{{ proto string intarray_to_json(string intarray)
   Returns contents of an intarray as JSON string */
PHP_FUNCTION(intarray_to_json) {
	int32_t *array;
	zval *var_array;
	unsigned int n;
	smart_str str;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &var_array) == FAILURE) {
		RETURN_FALSE;
	}

	if (intarray_check(var_array, -1) == FAILURE) {
		RETURN_FALSE;
	}

	array = INTARRAY_DATA(var_array);

	str.c = NULL;
	smart_str_appendc(&str, '[');
	for (n = 0; n < INTARRAY_LENGTH(var_array); n++) {
		if (n > 0) smart_str_appendc(&str, ',');
		smart_str_append_long(&str, (long)array[n]);
	}
	smart_str_appendc(&str, ']');
	smart_str_0(&str);

	RETURN_STRINGL(str.c, str.len, 0);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


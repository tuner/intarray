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

/* $Id: php_intarray.h,v 1.5 2009/10/18 19:06:07 tuner Exp $ */

#ifndef PHP_INTARRAY_H
#define PHP_INTARRAY_H

extern zend_module_entry intarray_module_entry;
#define phpext_intarray_ptr &intarray_module_entry

#ifdef PHP_WIN32
#define PHP_INTARRAY_API __declspec(dllexport)
#else
#define PHP_INTARRAY_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(intarray);
PHP_MSHUTDOWN_FUNCTION(intarray);
PHP_MINFO_FUNCTION(intarray);

PHP_FUNCTION(intarray_create);
PHP_FUNCTION(intarray_create_from_array);
PHP_FUNCTION(intarray_get);
PHP_FUNCTION(intarray_set);
PHP_FUNCTION(intarray_insert);
PHP_FUNCTION(intarray_delete);
PHP_FUNCTION(intarray_length);
PHP_FUNCTION(intarray_search);
PHP_FUNCTION(intarray_binarysearch_slot);
PHP_FUNCTION(intarray_binarysearch);
PHP_FUNCTION(intarray_intersect);
PHP_FUNCTION(intarray_sort);
PHP_FUNCTION(intarray_dump);
PHP_FUNCTION(intarray_to_json);
PHP_FUNCTION(intarray_union);
PHP_FUNCTION(intarray_difference);
PHP_FUNCTION(intarray_symmetric_difference);
PHP_FUNCTION(intarray_add);
PHP_FUNCTION(intarray_slice);
PHP_FUNCTION(intarray_shuffle);
PHP_FUNCTION(intarray_check);
PHP_FUNCTION(intarray_subset);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(intarray)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(intarray)
*/

/* In every utility function you add that needs to use variables 
   in php_intarray_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as INTARRAY_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define INTARRAY_G(v) TSRMG(intarray_globals_id, zend_intarray_globals *, v)
#else
#define INTARRAY_G(v) (intarray_globals.v)
#endif

#endif	/* PHP_INTARRAY_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */

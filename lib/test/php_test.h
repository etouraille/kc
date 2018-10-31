
#ifndef PHP_TEST_H
#define PHP_TEST_H

extern zend_module_entry test_module_entry;
#define phpext_test_ptr &test_module_entry

#define PHP_TEST_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_TEST_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_TEST_API __attribute__ ((visibility("default")))
#else
#	define PHP_TEST_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:

ZEND_BEGIN_MODULE_GLOBALS(test)
	zend_long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(test)
*/

/* Always refer to the globals in your function as TEST_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define TEST_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(test, v)

#if defined(ZTS) && defined(COMPILE_DL_TEST)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif	/* PHP_TEST_H */


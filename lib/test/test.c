
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_test.h"

/* If you declare any globals in php_test.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(test)
*/

/* True global resources - no need for thread safety here */
static int le_test;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("test.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_test_globals, test_globals)
    STD_PHP_INI_ENTRY("test.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_test_globals, test_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_test_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_test_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "test", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

PHP_FUNCTION(hello_world) {
    RETURN_STRING("Hello  World");
}

PHP_FUNCTION( test ) {

}

PHP_FUNCTION( vect ) {
        HashTable * x;
        HashTable * y;
        zval * z;
        int i = 0, j = 0;
        zval * val;
        zval * colval, rvc;
        Bucket p,q;

        int l,m;

        ZEND_PARSE_PARAMETERS_START(2, 2)
        Z_PARAM_ARRAY_HT(x)
        Z_PARAM_ARRAY_HT(y)
        ZEND_PARSE_PARAMETERS_END();



        array_init_size( return_value, l = zend_hash_num_elements( x ));
        zend_hash_real_init( Z_ARRVAL_P(return_value), 1);

        p = Z_ARRVAL_P(return_value)->arData[1];
        php_printf("Zval is a long with value %ld\n", l);

        //Z_ARRVAL_P(return_value)->arData = x->arData;
        z = emalloc(zend_hash_num_elements( x ) * sizeof(zval));
        val = emalloc(sizeof(zval));
        for(i=0;i<l;i++) {
            q = x->arData[i];
            //Z_ARRVAL_P(return_value)->arData[i].val = p.val;

            array_init_size( z+i , m=zend_hash_num_elements( y ));
            zend_hash_real_init( Z_ARRVAL_P(z+i), 1);
            for(j=0;j<m;j++) {
                p = y->arData[j];
                ZVAL_LONG(val,Z_LVAL(p.val)*Z_LVAL(q.val));
                zend_hash_index_add_new(Z_ARRVAL_P(z+i),j, val);
            }
            zend_hash_index_add_new(Z_ARRVAL_P(return_value),i, z+i);
        }


        efree(z);
        efree(val);


        /*
         ZEND_HASH_FILL_PACKED( Z_ARRVAL_P(return_value)) {
            // une allocation mémoire a faire sur les z en fonction de la taille.
               // Z_TYPE_P(val) = IS_STRING;
               p = x->arData[i];
               //ZVAL_COPY(val, &p.val);
               ZEND_HASH_FILL_ADD(&p.val);
               i ++;
        } ZEND_HASH_FILL_END();
         */



}

PHP_FUNCTION( example ) {
        zval    * zv;
        HashTable * myht;

        //ALLOC_HASHTABLE(myht);
        //zend_hash_init(myht, 0, NULL, ZVAL_PTR_DTOR, 0);

        //MAKE_STD_ZVAL( zv);
        //ZVAL_STRING(zv, "foo");

        //zend_hash_index_update(myht, LONG_MAX, zv );

        php_printf("Next \"free\" key: %ld\n", zend_hash_next_free_element(myht));
        //if (zend_hash_next_index_insert(myht, zv ) == FAILURE) {
        //    php_printf("next_index_insert failed\n");
        //}
        php_printf("Number of elements in hashtable: %ld\n", zend_hash_num_elements(myht));

        //zend_hash_destroy(myht);
        //FREE_HASHTABLE(myht);
}



/* {{{ php_test_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_test_init_globals(zend_test_globals *test_globals)
{
	test_globals->global_value = 0;
	test_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(test)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(test)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(test)
{
#if defined(COMPILE_DL_TEST) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(test)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(test)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "test support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ test_functions[]
 *
 * Every user visible function must have an entry in test_functions[].
 */
const zend_function_entry test_functions[] = {
	PHP_FE(confirm_test_compiled,	NULL)
	PHP_FE(hello_world, NULL)
    PHP_FE(example, NULL)
    PHP_FE(vect, NULL)
	PHP_FE_END	/* Must be the last line in test_functions[] */
};
/* }}} */

/* {{{ test_module_entry
 */
zend_module_entry test_module_entry = {
	STANDARD_MODULE_HEADER,
	"test",
	test_functions,
	PHP_MINIT(test),
	PHP_MSHUTDOWN(test),
	PHP_RINIT(test),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(test),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(test),
	PHP_TEST_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_TEST
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(test)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */


/*TITLE Trace Log */


#ifndef _LC_ASSERT_H__INCLUDED__
#define _LC_ASSERT_H__INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif


/** 
 *  Macro: LC_ASSERT
 *
 *  Check that the given condition is true, otherwise displays an error message
 *  and stops the program execution.  
 *
 *  Parameters:
 *      condition - Condition to verify.
 *      ... - Additional parameters, depending on the formatted string.
 */
#ifndef EXC_ASSERT
    #define LC_ASSERT_BASE(condition, arg1, arg2, arg3) { \
        if (!(condition)) { \
            LoaderCoreSPI_Stdlib_printf(arg1, arg2, arg3); \
            while(1){LoaderCoreSPI_Thread_Sleep(1);}; \
        } \
    }

    #define LC_ASSERT_ERROR                ("&Assert check failed at %s:%d\n")
    #define LC_ASSERT(condition)     LC_ASSERT_BASE(condition, LC_ASSERT_ERROR, __FILE__, __LINE__)
#else
    #define LC_ASSERT(condition)
#endif

#ifdef __cplusplus
}
#endif


#endif   /* _LC_ASSERT_H__INCLUDED__ */


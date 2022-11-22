
#ifndef _EZEXCEPTION_H
#define _EZEXCEPTION_H

#include <setjmp.h>

typedef struct Except
{
    const char *reason; // exception reason
} Except;

typedef struct ExceptFrame
{
    struct ExceptFrame *prev; // prev exception
    jmp_buf env;              // context env
    const char *path;         // file path
    int line;                 // file line num
    const Except *except;     // exception data
} ExceptFrame;

extern ExceptFrame *__ExceptStack__; // exception statck top pointer

enum
{
    __ExceptEntered__ = 0,
    __ExceptRaised__,
    __ExceptHandled__,
    __ExceptFinalized__,
};

// raise an exception with file path and line
void __ExceptRaise__(const Except *_except, const char *_path, const int line);

// raise an exception
#define RAISE(e) __ExceptRaise__(&e, __FILE__, __LINE__)

// reraise an exception
#define RERAISE __ExceptRaise__( \
    __ExceptFrame__.except, __ExceptFrame__.path, __ExceptFrame__.line)

// try, create a scope
#define TRY                                           \
    do                                                \
    {                                                 \
        volatile int __ExceptFlag__;                  \
        ExceptFrame __ExceptFrame__;                  \
        __ExceptFrame__.prev = __ExceptStack__;       \
        __ExceptStack__ = &__ExceptFrame__;           \
        __ExceptFlag__ = setjmp(__ExceptFrame__.env); \
        if (__ExceptEntered__ == __ExceptFlag__)      \
        {

// except, catch exception
#define EXCEPT(e)                                \
    if (__ExceptEntered__ == __ExceptFlag__)     \
        __ExceptStack__ = __ExceptStack__->prev; \
    }                                            \
    else if (__ExceptFrame__.except == &(e))     \
    {                                            \
        __ExceptFlag__ = __ExceptHandled__;

//
#define ELSE                                     \
    if (__ExceptEntered__ == __ExceptFlag__)     \
        __ExceptStack__ = __ExceptStack__->prev; \
    }                                            \
    else                                         \
    {                                            \
        __ExceptFlag__ = __ExceptHandled__;

//
#define FINALLY                                  \
    if (__ExceptEntered__ == __ExceptFlag__)     \
        __ExceptStack__ = __ExceptStack__->prev; \
    }                                            \
    {                                            \
        if (__ExceptEntered__ == __ExceptFlag__) \
            __ExceptFlag__ = __ExceptFinalized__;

// end try, end the scope of try
#define ENDTRY                                   \
    if (__ExceptEntered__ == __ExceptFlag__)     \
        __ExceptStack__ = __ExceptStack__->prev; \
    }                                            \
    if (__ExceptRaised__ == __ExceptFlag__)      \
        RERAISE;                                 \
    }                                            \
    while (0)                                    \
        ;

// replace `return` in try-except or try-finally
#define RETURN                                          \
    switch (__ExceptStack__ = __ExceptStack__->prev, 0) \
    default:                                            \
        return

#endif // _EZEXCEPTION_H


#include <stdlib.h>
#include <stdio.h>
#include "ezexcept.h"

ExceptFrame *__ExceptStack__ = 0;

void __ExceptRaise__(const Except *_except, const char *_path, const int _line)
{
    ExceptFrame *ef = __ExceptStack__;
    if (0 == ef)
    {
        fprintf(stderr, "Uncaught exception");
        if (_except->reason)
            fprintf(stderr, ": %s", _except->reason);
        else
            fprintf(stderr, " at 0x%p", _except);
        if (_path && _line > 0)
            fprintf(stderr, "\n\traised at %s:%d\n", _path, _line);
        fprintf(stderr, "aborting...\n");
        fflush(stderr);
        abort();
    }
    ef->except = _except;
    ef->path = _path;
    ef->line = _line;
    __ExceptStack__ = __ExceptStack__->prev;
    longjmp(ef->env, __ExceptRaised__);
}


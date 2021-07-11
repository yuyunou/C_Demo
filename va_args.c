#include <stdarg.h>


void log_printf(char format, ...)
{
    va_arg va;
    va_start();
    
    va_end();


}


#define LOG_PRINTF(tar, lev , format, ...)\
    do\
    {\
        log_printf(format);\
    }while(0)






#include <stdio.h>
#include <stdarg.h>


void log_printf(char *format, ...)
{
    va_list va;
    char buf[256] = {0};
    va_start(va, format);
    vsprintf(buf, format, va);
    va_end(va);
    printf(buf, buf);
}


#define LOG_PRINTF(tar, lev , format, ...)\
    do\
    {\
        log_printf(format, __VA_ARGS__);\
    }while(0)


int main()

{
    int a = 12;
    LOG_PRINTF(0 , 0, "yyo tttt %d", a);

    //log_printf("yyo tttt %d", a);
}

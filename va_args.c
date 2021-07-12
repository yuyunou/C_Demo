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




int sum(int a, ...)
{
    int sum = 0;
    va_list va;
    va_start(va, a);

    while (a--)
    {
        sum += va_arg(va, int);
    }

    va_end(va);

    return sum;

}



int main()

{
    int a = 12;
    LOG_PRINTF(0 , 0, "yyo tttt %d", sum(4, 2 ,3 , 1, 77));

    //log_printf("yyo tttt %d", a);
}

/* Revise minprintf to handle more of the facilities of printf .
   */

#include<stdio.h>

#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...)
{
    va_list list;
    char *p, *sval;
    int ival;
    double dval;
    unsigned uval;

    va_start(list, fmt);
    for (p = fmt; *p; p++) {
        if (*p != '%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
        case 'd':
        case 'i':
            ival = va_arg(list, int);
            printf("%d", ival);
            break;
        case 'c':
            ival = va_arg(list, int);
            putchar(ival);
            break;
        case 'u':
            uval = va_arg(list, unsigned int);
            printf("%u", uval);
            break;
        case 'o':
            uval = va_arg(list, unsigned int);
            printf("%o", uval);
            break;
        case 'x':
            uval = va_arg(list, unsigned int);
            printf("%x", uval);
            break;
        case 'X':
            uval = va_arg(list, unsigned int);
            printf("%X", uval);
            break;
        case 'e':
            dval = va_arg(list, double);
            printf("%e", dval);
            break;
        case 'f':
            dval = va_arg(list, double);
            printf("%f", dval);
            break;
        case 'g':
            dval = va_arg(list, double);
            printf("%g", dval);
            break;
        case 's':
            for (sval = va_arg(list, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(list);
}

int main(void){
	char *str="Akil";
	minprintf("Hello %s",str);	
	return 0;
}

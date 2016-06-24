/*
  Write a private version of scanf analogous to minprintf from the previous section.
  */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define MAXLEN 100

void minscanf(char *fmt, ...){
  va_list list;
  char *p;
  int *ival;
  char line[MAXLEN];

  va_start(list, fmt);

  for (p = fmt; *p; p++) {
    if (*p != '%')
      continue;
    switch(*++p) {
      case 'd':
        ival = va_arg(list, int *);
        fgets(line,MAXLEN,stdin);
        line[strlen(line)-1] = '\0'; // Avoid newline
        *ival = atoi(line);
        break;
      default:
        break;
    }
  }
}

int main(void){
  int k;
  minscanf("%d", &k);
  printf("Result from minscanf: %d\n", k);
  return 0;
}

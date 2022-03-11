#include <stdio.h>

#include "calc.h"
#include "string_handle.h"

int getop(char s[]) {
  int i, c;

  while (is_space(s[0] = c = buffer_getchar()))
    ;
  s[1] = '\0';

  i = 0;

  if (! is_digit(c)) {
    switch (c) {
    case '.':
      break;

    case '-':
    case '+':
      c = buffer_getchar();
      if (! is_digit(c)) {
        buffer_ungetchar(c);
        return s[0];
      }
      s[++i] = c;
      break;

    default:
      return c;
      break;
    }
  }

  if (is_digit(c))
    while(is_digit(s[++i] = c = buffer_getchar()))
      ;

  if (c == '.')
    while (is_digit(s[++i] = c = buffer_getchar()))
      ;
  s[i] = '\0';

  if (c != EOF)
    buffer_ungetchar(c);

  return NUMBER;
}


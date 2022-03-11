#include <stdio.h>

#include "calc.h"

char buffer[BUFFER_SIZE];
int buffer_free_position = 0;

int buffer_getchar(void) {
  return (buffer_free_position > 0) ? (buffer[--buffer_free_position]) : (getchar());
}

void buffer_ungetchar(int c) {
  if (buffer_free_position >= BUFFER_SIZE)
    printf("### Error: buffer is full! ###\n");
  else
    buffer[buffer_free_position++] = c;
}

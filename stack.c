#include <stdio.h>

#include "calc.h"

int stack_free_position = 0;
double stack[STACK_SIZE];

void stack_push(double item) {
  if (stack_free_position < STACK_SIZE)
    stack[stack_free_position++] = item;
  else
    printf("### Error: stack if full! Can't hold %f! ###\n", item);
}

double stack_pop(void) {
  if (stack_free_position > 0)
    return stack[--stack_free_position];
  else {
    printf("### Error: stack is empty! ### \n");
    return 0.0;
  }
}

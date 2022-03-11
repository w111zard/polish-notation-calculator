#include <stdio.h>
#include <math.h>

#include "string_handle.h"
#include "calc.h"


int main(int argc, char **argv) {
  char s[OPERATIONS_LIMIT];

  double op2;
  int type;
  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      stack_push(string_to_double(s));
      break;

    case '+':
      stack_push(stack_pop() + stack_pop());
      break;

    case '-':
      op2 = stack_pop();
      stack_push(stack_pop() - op2);
      break;

    case '*':
      stack_push(stack_pop() * stack_pop());
      break;

    case '/':
      op2 = stack_pop();
      if (op2 == 0) {
        printf("### Error: division by zero! ###\n");
        return 1;
      }
      stack_push(stack_pop() / op2);
      break;

    case '%':
      op2 = stack_pop();
      stack_push(fmod(stack_pop(), op2));
      break;

    case '\n':
      printf("%f\n", stack_pop());
      break;

    default:
      printf("### Error: unknown operation '%c' ! ###\n", type);
      return 2;
      break;
    }
  }

  return 0;
}

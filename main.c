#include <stdio.h>
#include <math.h>

enum {
  STACK_SIZE = 100,
  BUFFER_SIZE = 100,
  OPERATIONS_LIMIT = 100,
  NUMBER = 1
};

/* STACK */

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

/* ! STACK */

/* BUFFER */

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

/* ! BUFFER */

int is_space(char c) {
  return (c == ' ') || (c == '\t');
}

int is_digit(char c) {
  return (c >= '0') && (c <= '9');
}

int char_to_number(char c) {
  return c - '0';
}

double calculate_power(double value, int n) {
  if (n == 0)
    return 1;
  else
    return value * calculate_power(value, n - 1);
}

double string_to_double(char s[]) {
  int i;
  for (i = 0; is_space(s[i]); ++i)
    ;

  int sign = (s[i] == '-') ? (-1) : (1);
  if ((s[i] == '+') || (s[i] == '-'))
    ++i;

  double value;
  for (value = 0.0; is_digit(s[i]); ++i)
    value = 10.0 * value + char_to_number(s[i]);

  if (s[i] == '.')
    ++i;

  double power;
  for (power = 1.0; is_digit(s[i]); ++i) {
    value = 10.0 * value + char_to_number(s[i]);
    power *= 10.0;
  }

  if ((s[i] == 'e') || (s[i] == 'E'))
    ++i;

  int e_sign = (s[i] == '-') ? (-1) : (1);
  if ((s[i] == '-') || (s[i] == '+'))
    ++i;

  int e_value;
  for (e_value = 0; is_digit(s[i]); ++i)
    e_value = 10 * e_value + char_to_number(s[i]);

  if (e_sign == -1)
    power *= calculate_power(10, e_value);
  else
    value *= calculate_power(10, e_value);

  return sign * (value / power);
}

int string_to_int(char s[]) {
  return (int) string_to_double(s);
}

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


int main(int argc, char **argv) {
  char s[OPERATIONS_LIMIT];
  double op1;
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

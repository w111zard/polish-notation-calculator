#include "string_handle.h"

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

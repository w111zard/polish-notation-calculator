#include <stdio.h>

int is_space(char symbol) {
  return (symbol == ' ');
}

int is_digit(char symbol) {
  return (symbol >= '0' && symbol <= '9');
}

int char_to_int(char symbol) {
  return (symbol - '0');
}

double my_atof(char s[]) {
  // skip spaces symbols
  int i;
  for (i = 0; is_space(s[i]); ++i)
    ;

  // check for sign
  int sign = 1;
  if (s[i] == '-') {
    sign = -1;
    ++i;
  }
  else if (s[i] == '+') {
    ++i;
  }

  double value;
  for (value = 0.0; is_digit(s[i]); ++i)
    value = 10.0 * value + char_to_int(s[i]);

  if (s[i] == '.')
    ++i;

  double power;
  for (power = 1.0; is_digit(s[i]); ++i) {
    value = 10.0 * value + char_to_int(s[i]);
    power *= 10.0;
  }

  if ((s[i] == 'e') || (s[i] == 'E'))
    ++i;

  int m_sign = 1;
  if (s[i] == '-') {
    m_sign = -1;
    ++i;
  }
  else if (s[i] == '+') {
    ++i;
  }

  int mantiss;
  for (mantiss = 0; is_digit(s[i]); ++i)
    mantiss = 10 * mantiss + char_to_int(s[i]);

  for (int j = 0; j < mantiss; ++j) {
    if (m_sign == -1)
      power *= 10;
    else
      value *= 10;
  }

  return sign * (value / power);
}

int my_atoi(char s[]) {
  return (int) my_atof(s);
}

int my_getline(char s[], int lim) {
  int ch;
  int i = 0;
  while (--lim > 0 && (ch = getchar()) && ch != '\n')
    s[i++] = ch;

  if (ch == '\n')
    s[i++] = '\n';

  s[i] = '\0';

  return i;
}

int main() {
  char line[100];

  while (my_getline(line, 100)) {
    double res = my_atof(line);
    printf("%f\n", res);
  }

  return 0;
}

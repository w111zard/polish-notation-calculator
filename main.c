#include <stdio.h>

#include "my_string.h"

int main() {
  char line[100];

  while (my_getline(line, 100)) {
    double res = my_atof(line);
    printf("%f\n", res);
  }

  return 0;
}

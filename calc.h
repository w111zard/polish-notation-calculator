#ifndef __CALC_H__
#define __CALC_H__

enum {
  STACK_SIZE = 100,
  BUFFER_SIZE = 100,
  OPERATIONS_LIMIT = 100,
  NUMBER = 1
};


/* STACK */
extern int stack_free_position;
extern double stack[];

void stack_push(double item);
double stack_pop(void);
/* ! STACK */


/* BUFFER */
extern char buffer[];
extern int buffer_free_position;

int buffer_getchar(void);
void buffer_ungetchar(int c);
/* ! BUFFER  */


/* GETOP */
int getop(char s[]);
/* ! GETOP */

#endif /* #ifndef __CALC_H__ */

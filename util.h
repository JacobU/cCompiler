/* util.h */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * string;
string String(char *);
typedef char bool;
#define TRUE 1
#define FALSE 0

void *checked_malloc(int len);
string String(char *s);
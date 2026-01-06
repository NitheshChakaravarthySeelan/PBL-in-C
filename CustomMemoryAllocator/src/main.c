#include "allocator.h"
#include <stdio.h>
#include <string.h>

int main(void) {
  printf("Simple allocator test\n\n");

  char *a = my_malloc(32);
  char *b = my_malloc(64);

  strcpy(a, "hello");
  strcpy(b, "world");

  printf("a: %s\n", a);
  printf("b: %s\n", b);

  my_free(a);
  my_free(b);

  printf("\nFreed a and b\n");

  char *c = my_malloc(16);
  strcpy(c, "reuse");

  printf("c: %s\n", c);

  my_free(c);

  printf("\nAllocator test complete\n");
  return 0;
}

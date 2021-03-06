#include <stdio.h>
#include "test-single-file.h"

# define TEST(foo) if (foo) { printf("foo"); }
int global = 0;

/// Test comment.
int test() {
  printf("this is a test");

  {
    int a = 9;
    printf("this is another test: %d", a);

  }

  return 3;
}

// This is a pre-existing comment.
/** Test comment */
int main(void) {
  int value = 12;
  if (1) { value = test();
    if (value > 5) {
      printf("this is a second test");
    }
  }

  toast foo = {0, 100};
  while (foo.foo != foo.bar) {
    printf("this is another test %d", foo.foo);
    ++foo.foo;
  }
  global += 3;
  TEST(value);
  return 0;
}

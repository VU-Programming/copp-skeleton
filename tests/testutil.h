#ifndef TESTUTIL_H
#define TESTUTIL_H
#include <stdbool.h>
#include <stdlib.h>

// Disable abort on err using -DABORT_ON_ERR=0
// E.g. USERFLAGS=-DABORT_ON_ERR=0 make test1
#ifndef ABORT_ON_ERR
#define ABORT_ON_ERR 1
#endif

#define RUN_TEST(fun) __run_test(fun, #fun);
#define END_TEST() __print_test_result(__FILE__);
#define __assert(c) do { \
  if (!(c)) { \
    fprintf(stderr, "Assertion error '%s' in %s:%d\n", #c, __FILE__, __LINE__); \
    __assert_errs++; \
    if(ABORT_ON_ERR) abort(); \
  } \
} while (0);

#define assert(c) __assert(c);

void steps(int n);

static int __passed_test_counter = 0;
static int __failed_test_counter = 0;

static int __assert_errs;

/*
 * Test functions should follow the following format:
 * void mytest(),
 * calling assert() on all assertions.
 */
static void __run_test(void (*f)(void), char *tname) {
  __assert_errs = 0;
  f();
  if (!__assert_errs) {
    __passed_test_counter++;
    return;
  }
  __failed_test_counter++;
  fprintf(stderr, "  [FAIL] Failed test %s\n", tname);
}


static int __print_test_result(char *test_name) {
  int total = __passed_test_counter + __failed_test_counter;
  char *msg = "[FAIL]";
  if (total == __passed_test_counter) {
    msg = "[Ok]";
  }
  fprintf(stderr, "========================================\n");
  fprintf(stderr, "## %s passed %d/%d tests in %s##\n", msg, __passed_test_counter, total, test_name);

  return total == __passed_test_counter ? 0 : 1;
}

void steps(int n)
{
    for (int i = 0; i < n; i++)
        step();
}

FILE *set_null_output(void)
{
    FILE *fh = fopen("/dev/null", "w");
    set_output(fh);
    return fh;
}

#endif

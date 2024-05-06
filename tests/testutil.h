#ifndef TESTUTIL_H
#define TESTUTIL_H
#include <stdbool.h>
#include <stdlib.h>

/**
 * DO NOT MODIFY THIS FILE.
 **/

#define _GNU_SOURCE
#define __USE_GNU
#include <dlfcn.h>
// if you want to make use of exit() in your tests, use orig_exit() instead

void orig_exit(int status) __attribute__((__noreturn__));

void exit(int __status) __THROW __attribute__ ((__noreturn__));

typedef void (*exit_handle)(int);

void orig_exit(int status)
{
  static exit_handle _orig_exit;
  if (!_orig_exit)
    _orig_exit = (exit_handle)dlsym(RTLD_NEXT, "exit");
  _orig_exit(status);
  abort(); // will never be called, used to suppress a compiler warning!
}

void exit(int status)
{
  if(status == 0){
    fprintf(stderr, "ALERT! INVALID USE OF EXIT() DETECTED. "
                  "You risk a failing grade if you submit "
                  "with exit(0) in your code.\n");
    abort();
  } else {
    orig_exit(status);
  }

}

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

void steps(ijvm* m, int n);

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

void steps(ijvm* m, int n)
{
    for (int i = 0; i < n; i++)
        step(m);
}

FILE *get_null_output(void)
{
    FILE *fh = fopen("/dev/null", "w");
    return fh;
}

int *set_null_output(void)
{
    FILE *fh = fopen("/dev/null", "w");
    return (int*) fh;
}

#endif

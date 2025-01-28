#ifndef TESTUTIL_H
#define TESTUTIL_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 * DO NOT MODIFY THIS FILE.
 **/

#define _GNU_SOURCE
#define __USE_GNU
#include <dlfcn.h>

void *malloc(size_t size);
void exit(int __status) ;

typedef void (*exit_handle)(int);
typedef void *(*malloc_handle)(size_t size);

void * malloc(size_t size)
{
  static malloc_handle _orig_malloc;
  if (!_orig_malloc)
    _orig_malloc = (malloc_handle)dlsym(RTLD_NEXT, "malloc");
  void* mem = _orig_malloc(size);
  // set memory to 0xFF to catch use of uninitialized memory
  memset(mem, 0xFF, size);
  return mem;
}


void exit(int __status)
{
  static exit_handle _orig_exit;
  if (!_orig_exit)
    _orig_exit = (exit_handle)dlsym(RTLD_NEXT, "exit");
  if(__status == 0){
    fprintf(stderr, "ALERT! INVALID USE OF EXIT() DETECTED. "
                  "You risk a failing grade if you submit "
                  "with exit(0) in your code.\n");
    abort();
  } else {
   _orig_exit(__status);
  }
  abort();
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

#ifdef assert
#  undef assert
#endif

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

#endif

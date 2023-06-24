#ifndef INTERCEPT_H
#define INTERCEPT_H

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

void orig_exit(int status) __attribute__((__noreturn__));

void exit(int status) __attribute__((__noreturn__));

#endif // INTERCEPT_H

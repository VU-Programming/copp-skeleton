#include "intercept.h"

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
  status--; // to suppress pedantic warnings
  fprintf(stderr, "Do not use exit in the basic functionalities."
                  " You won't be graded correctly if you do!\n");
  orig_exit(1);
}

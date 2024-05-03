#include <stdio.h>
#include "ijvm.h"
#include "util.h"
static void print_help(void)
{ 
  printf("Usage: ./ijvm binary \n"); 
}

int main(int argc, char **argv) 
{

  if (argc < 2) 
  {
    print_help();
    return 1;
  }
  ijvm* m = init_ijvm_std(argv[1]);
  if (m == NULL) 
  {
    fprintf(stderr, "Couldn't load binary %s\n", argv[1]);
    return 1;
  }

  run(m);

  destroy_ijvm(m);

  return 0;
}

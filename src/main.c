#include <stdio.h>
#include "ijvm.h"
#include "util.h"
void print_help(void)
{ 
  printf("Usage: ./ijvm binary \n"); 
}

int main(int argc, char **argv) 
{
  d5printf("HELLO!");
  if (argc < 2) 
  {
    print_help();
    return 1;
  }

  if (init_ijvm(argv[1]) < 0) 
  {
    fprintf(stderr, "Couldn't load binary %s\n", argv[1]);
    return 1;
  }

  run();

  destroy_ijvm();

  return 0;
}

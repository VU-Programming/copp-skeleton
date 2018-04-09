#include <stdio.h>
#include "ijvm.h"

void print_help()
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

  if (init_ijvm(argv[1]) < 0)
  {
      fprintf(stderr, "Couldn't load binary %s\n", argv[1]);
      return 1;
  }

  run();

  destroy_ijvm();

  return 0;
}

#include <ijvm.h>

// ijvm.h for descriptions of these functions

FILE* in;  // use getc(in) to get a character from in
FILE* out; // use for example fprintf(out, "Test %d %d", 3 2 ) to print to out

void set_input(FILE *fp)
{
  in = fp;
}

void set_output(FILE *fp)
{
  out = fp;
}


int init_ijvm(char *binary_path)
{
    in = stdin;
    out = stdout;
    //TODO: implement me
    return -1;
}

void destroy_ijvm(void)
{
    //TODO: implement me
}

byte_t *get_text(void)
{
    //TODO: implement me
    return NULL;
}

int get_text_size(void)
{
    //TODO: implement me
    return -1;
}

word_t get_constant(int i)
{
  // TODO: implement me
  return 0;
}

int get_program_counter(void)
{
    //TODO: implement me
    return -1;
}

word_t tos(void)
{
  // TODO: implement me
  return -1;
}

bool finished(void)
{
  // TODO: implement me
  return false;
}

word_t get_local_variable(int i)
{
  // TODO: implement me
  return 0;
}

bool step(void)
{
    //TODO: implement me
    return true;
}

void run(void)
{
  while(!finished())
  {
    step();
  }
}


byte_t get_instruction(void)
{
    return get_text()[get_program_counter()];
}
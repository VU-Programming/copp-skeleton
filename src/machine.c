#include <ijvm.h>

int init_ijvm(char *binary_file)
{
  // Implement loading of binary here
  return -1;
}

void destroy_ijvm()
{
  // Reset IJVM state
}

void run()
{
  // Step while you can
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}

byte_t *get_text()
{
  // TODO: implement me
  return NULL;
}

int text_size()
{
  // TODO: implement me
  return 0;
}

int get_program_counter()
{
  // TODO: implement me
  return 0;
}

byte_t get_instruction()
{
  //TODO: implement me
  return 0;
}

word_t tos()
{
  // TODO: implement me
  return 0;
}

word_t *get_stack()
{
  // TODO: implement me
  return NULL;
}

int stack_size()
{
  // TODO: implement me
  return 0;
}

bool step()
{
  // TODO: implement me
  return false;
}

bool finished()
{
  // TODO: implement me
  return false;
}

word_t get_local_variable(int i)
{
  // TODO: implement me
  return 0;
}

word_t get_constant(int i)
{
  // TODO: implement me
  return 0;
}

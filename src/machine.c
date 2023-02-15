#include <ijvm.h>

byte_t *get_text(void)
{
    return NULL;
}

int get_text_size(void)
{
    return -1;
}

int get_program_counter(void)
{
    return -1;
}

bool step(void)
{
    return true;
}

void run(void)
{

}

byte_t get_instruction(void)
{
    return 0;
}

void set_input(FILE *fp)
{

}

void set_output(FILE *fp)
{

}

int init_ijvm(char *binary_path)
{
    return -1;
}

void destroy_ijvm(void)
{

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

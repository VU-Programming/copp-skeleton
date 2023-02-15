#include <ijvm.h>

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

int get_program_counter(void)
{
    //TODO: implement me
    return -1;
}

bool step(void)
{
    //TODO: implement me
    return true;
}

void run(void)
{
  //TODO: implement me
}

byte_t get_instruction(void)
{
    //TODO: implement me
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
    //TODO: implement me
    return -1;
}

void destroy_ijvm(void)
{
    //TODO: implement me
}

word_t tos(void)
{
  // TODO: implement me
  return 0;
}

word_t *get_stack(void)
{
  // TODO: implement me
  return NULL;
}

int stack_size(void)
{
  // TODO: implement me
  return 0;
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

word_t get_constant(int i)
{
  // TODO: implement me
  return 0;
}

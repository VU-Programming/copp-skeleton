#include <stdio.h>  // for getc, printf
#include <stdlib.h> // malloc, free
#include "ijvm.h"
#include "util.h" // read this file for debug prints, endianness helper functions


// see ijvm.h for descriptions of the below functions

ijvm* init_ijvm(char *binary_path, FILE* input , FILE* output) 
{
  // do not change these first three lines
  ijvm* m = (ijvm *) malloc(sizeof(ijvm));
  m->in = input;
  m->out = output;

  // TODO: implement me

  return m;
}

void destroy_ijvm(ijvm* m) 
{
  // TODO: implement me

  free(m); // free memory for struct
}

byte_t *get_text(ijvm* m) 
{
  // TODO: implement me
  return NULL;
}

unsigned int get_text_size(ijvm* m) 
{
  // TODO: implement me
  return 0;
}

word_t get_constant(ijvm* m,int i) 
{
  // TODO: implement me
  return 0;
}

unsigned int get_program_counter(ijvm* m) 
{
  // TODO: implement me
  return 0;
}

word_t tos(ijvm* m) 
{
  // this operation should NOT pop (remove top element from stack)
  // TODO: implement me
  return -1;
}

bool finished(ijvm* m) 
{
  // TODO: implement me
  return false;
}

word_t get_local_variable(ijvm* m, int i) 
{
  // TODO: implement me
  return 0;
}

void step(ijvm* m) 
{
  // TODO: implement me

}

byte_t get_instruction(ijvm* m) 
{ 
  return get_text(m)[get_program_counter(m)]; 
}

ijvm* init_ijvm_std(char *binary_path) 
{
  return init_ijvm(binary_path, stdin, stdout);
}

void run(ijvm* m) 
{
  while (!finished(m)) 
  {
    step(m);
  }
}


// Below: methods needed by bonus assignments, see ijvm.h

//int get_call_stack_size(void) 
//{
   // TODO: implement me
//   return sp;
//}


// Checks if reference is a freed heap array. Note that this assumes that 
// 
//bool is_heap_freed(word_t reference) 
//{
   // TODO: implement me
// return 0;
//}

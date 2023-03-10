#include <ijvm.h>
#include <stdio.h> // for getc, printf 

#define DEBUG_LEVEL 1
/* Adjust the above value to 0 to 5 to control debug prints.

 The file util.h defines several macros for debug prints, 
namely dprintf, d2printf, d3printf, d4printf and d5printf.

Which debug prints give outputs and which do not depends on the debug level.
If the debug level is 0, no debug prints will be printed. If the debug level
is n, all prints with a debug level less than or equal to n will be printed.

Debug prints which are disabled are not compiled into the program, so they
do not affect performance.

This gives you a method to log all kinds of things for debugging, and control
the granularity with a single variable. 

Example: d2printf("Current program text %02x %02x\n", text[pc] , text[pc+1]);
*/


// see ijvm.h for descriptions of the below functions


FILE* in;  // use fgetc(in) to get a character from in. 
           //This will return EOF if no char is available.
FILE* out; // use for example fprintf(out, "%c", value); to print value to out

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
  // this operation should NOT pop (remove top element from stack)
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

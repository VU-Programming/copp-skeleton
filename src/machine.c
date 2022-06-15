#include <ijvm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utilities.h"
#include "stackStruct.h"

static uint8_t *txtPointer = NULL;
static uint32_t *txtSizePointer = NULL;
static uint32_t *cnstPointer = NULL;
static uint32_t *cnstSizePointer = NULL;
static uint8_t *programCounter = NULL;
stack_t *stackMemory = NULL;

static int pc = 0;

int init_ijvm(char *binary_file)
{
  FILE*fp;
  fp = fopen(binary_file, "rb");

  uint32_t fileHeader;
  uint32_t cnstOrigin;
  uint32_t* cnstSize = (uint32_t*) malloc(sizeof(uint32_t));
  uint32_t txtOrigin;
  uint32_t* txtSize = (uint32_t*) malloc(sizeof(uint32_t));
  

  fread(&fileHeader, sizeof(uint32_t), 1, fp);
  fileHeader = swap_uint32(fileHeader);

  if(fileHeader == MAGIC_NUMBER)
  {
    fread(&cnstOrigin, sizeof(uint32_t), 1, fp);
    cnstOrigin = swap_uint32(cnstOrigin);
    //printf("con: %x\n", cnstOrigin);

    fread(cnstSize, sizeof(uint32_t), 1, fp);
    *cnstSize = swap_uint32(*cnstSize);
    //printf("size: %d\n", *cnstSize);
    cnstSizePointer = cnstSize;

    uint32_t* cnst = (uint32_t*) malloc(*cnstSize);
    fread(cnst, sizeof(uint32_t), *cnstSize/4, fp);
    for(int i = 0; i < *cnstSize/4; i++)
    {
      cnst[i] = swap_uint32(cnst[i]);
    }
    cnstPointer = cnst;

    fread(&txtOrigin, sizeof(uint32_t), 1, fp);
    txtOrigin = swap_uint32(txtOrigin);
    //printf("txtorigin: %x\n", txtOrigin);

    fread(txtSize, sizeof(uint32_t), 1, fp);
    *txtSize = swap_uint32(*txtSize);
    //printf("size: %d\n", *txtSize);
    txtSizePointer = txtSize;

    uint8_t* txt = (uint8_t*) malloc(*txtSize);
    fread(txt, sizeof(uint8_t), *txtSize, fp);
    //printf("size: %x %x %x %x %x %x %x\n", txt[0], txt[1], txt[2], txt[3], txt[4], txt[5], txt[6]);
    txtPointer = txt;
    programCounter = &txt[0];

    return 0;
  }
  else
  {
    return -1;
  }
}

void destroy_ijvm()
{

}

int get_program_counter()
{
  return pc;
}

byte_t get_instruction()
{
  return *programCounter;
}

bool step()
{
  printInstruction(get_instruction());
  programCounter = programCounter + sizeof(uint8_t);
  if(isInstruction(get_instruction()) == true)
  {
    pc++;
    return true;
  }
  else
  {
    return false;
  }
}

void run()
{
  while(true)
  {
    if(step() == false)
    {
      break;
    } 
  }
}

int text_size()
{
  return *txtSizePointer;
}

byte_t *get_text(void)
{
  return txtPointer;
}

void set_input(FILE *fp)
{
  // TODO: implement me
}

void set_output(FILE *fp)
{
  // TODO: implement me
}

word_t tos()
{
  return stackMemory->value;
}
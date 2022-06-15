#include <stdio.h>  
#include <stdint.h>  
#include <stdbool.h>
#include <ijvm.h> 

static uint32_t swap_uint32(uint32_t num)
{
  return((num>>24)&0xff) | ((num<<8)&0xff0000) |((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

bool isInstruction(uint8_t currentByte)
{
  bool temp;
  switch (currentByte)
  {
  case OP_BIPUSH:
    temp = true;
    break;
  case OP_DUP:
    temp = true;
    break;
  case OP_ERR:
    temp = true;
    break;
  case OP_GOTO:
    temp = true;
    break;    
  case OP_HALT:
    temp = false;
    break;
  case OP_IADD:
    temp = true;
    break;
  case OP_IAND:
    temp = true;
    break;
  case OP_IFEQ:
    temp = true;
    break;
  case OP_IFLT:
    temp = true;
    break;
  case OP_ICMPEQ:
    temp = true;
    break;
  case OP_IINC:
    temp = true;
    break;
  case OP_ILOAD:
    temp = true;
    break;
  case OP_IN:
    temp = true;
    break;
  case OP_INVOKEVIRTUAL:
    temp = true;
    break; 
  case OP_IOR:
    temp = true;
    break; 
  case OP_IRETURN:
    temp = true;
    break; 
  case OP_ISTORE:
    temp = true;
    break; 
  case OP_ISUB:
    temp = true;
    break; 
  case OP_LDC_W:
    temp = true;
    break; 
  case OP_NOP:
    temp = true;
    break; 
  case OP_OUT:
    temp = true;
    break;
  case OP_POP:
    temp = true;
    break;
  case OP_SWAP:
    temp = true;
    break;     
  case OP_WIDE:
    temp = true;
    break; 
  default:
    temp = true;
    break;
  }
  return temp;
}

void printInstruction(uint8_t currentByte)
{
  switch (currentByte)
  {
  case OP_BIPUSH:
    printf("BIPUSH\n");
    break;
  case OP_DUP:
    printf("DUP\n");
    break;
  case OP_ERR:
    printf("ERR\n");
    break;
  case OP_GOTO:
    printf("GOTO\n");
    break;    
  case OP_HALT:

    break;
  case OP_IADD:
    printf("IADD\n");
    break;
  case OP_IAND:
    printf("IAND\n");
    break;
  case OP_IFEQ:
    printf("IFEQ\n");
    break;
  case OP_IFLT:
    printf("IFLT\n");
    break;
  case OP_ICMPEQ:
    printf("ICMPEQ\n");
    break;
  case OP_IINC:
    printf("IINC\n");
    break;
  case OP_ILOAD:
    printf("ILOAD\n");
    break;
  case OP_IN:
    printf("IN\n");
    break;
  case OP_INVOKEVIRTUAL:
    printf("INVOKEVIRTUAL\n");
    break; 
  case OP_IOR:
    printf("IOR\n");
    break; 
  case OP_IRETURN:
    printf("IRETURN\n");
    break; 
  case OP_ISTORE:
    printf("ISTORE\n");
    break; 
  case OP_ISUB:
    printf("ISUB\n");
    break; 
  case OP_LDC_W:
    printf("LDC_W\n");
    break; 
  case OP_NOP:
    printf("NOP\n");
    break; 
  case OP_OUT:
    printf("OUT\n");
    break;
  case OP_POP:
    printf("POP\n");
    break;
  case OP_SWAP:
    printf("SWAP\n");
    break;     
  case OP_WIDE:
    printf("WIDE\n");
    break; 
  default:

    break;
  }
}
#ifndef IJVM_H
#define IJVM_H

#include <stdio.h>  /* contains type FILE * */
#include <stdint.h>  /* contains exact integer types int32_t, uint8_t */
#include <stdbool.h> /* contains the boolean */

#include "ijvm_types.h"
#include "ijvm_struct.h"

#define MAGIC_NUMBER 0x1DEADFAD

#define OP_BIPUSH         ((byte) 0x10)
#define OP_DUP            ((byte) 0x59)
#define OP_ERR            ((byte) 0xFE)
#define OP_GOTO           ((byte) 0xA7)
#define OP_HALT           ((byte) 0xFF)
#define OP_IADD           ((byte) 0x60)
#define OP_IAND           ((byte) 0x7E)
#define OP_IFEQ           ((byte) 0x99)
#define OP_IFLT           ((byte) 0x9B)
#define OP_IF_ICMPEQ      ((byte) 0x9F)
#define OP_IINC           ((byte) 0x84)
#define OP_ILOAD          ((byte) 0x15)
#define OP_IN             ((byte) 0xFC)
#define OP_INVOKEVIRTUAL  ((byte) 0xB6)
#define OP_IOR            ((byte) 0xB0)
#define OP_IRETURN        ((byte) 0xAC)
#define OP_ISTORE         ((byte) 0x36)
#define OP_ISUB           ((byte) 0x64)
#define OP_LDC_W          ((byte) 0x13)
#define OP_NOP            ((byte) 0x00)
#define OP_OUT            ((byte) 0xFD)
#define OP_POP            ((byte) 0x57)
#define OP_SWAP           ((byte) 0x5F)
#define OP_WIDE           ((byte) 0xC4)

// Bonus assignment instructions
#define OP_TAILCALL       ((byte) 0xCB)

#define OP_NEWARRAY       ((byte) 0xD1)
#define OP_IALOAD         ((byte) 0xD2)
#define OP_IASTORE        ((byte) 0xD3)

#define OP_GC             ((byte) 0xD4)

#define OP_NETBIND        ((byte) 0xE1)
#define OP_NETCONNECT     ((byte) 0xE2)
#define OP_NETIN          ((byte) 0xE3)
#define OP_NETOUT         ((byte) 0xE4)
#define OP_NETCLOSE       ((byte) 0xE5)
/**
 * DO NOT MODIFY THIS FILE.
 **/



/**
 * Initializes the IJVM with the binary file found at the provided argument.
 * input gives the file where the ijvm reads from for the IN command
 * output gives the file where the ijvm writes to for the OUT command
 *
 * Returns  - A pointer to an ijvm struct on success
 *          - NULL on failure
 **/
ijvm* init_ijvm(char *binary_path, FILE* input , FILE* output);


/**
 * Destroys a vm, that is to say, free all memory associated with the machine
 * and allow for a new call to init_ijvm().
 */
void destroy_ijvm(ijvm* m);

/**
 * Returns the currently loaded program text as a byte array.
 **/
byte *get_text(ijvm* m);


/**
 * Returns the size of the currently loaded program text.
 **/
unsigned int get_text_size(ijvm* m);

/**
 * @param i index of the constant to obtain
 * @return The constant at location i in the constant pool.
 **/
word get_constant(ijvm* m, int i);


/**
 * Returns the value of the program counter (as an offset from the first instruction).
 **/
unsigned int get_program_counter(ijvm* m);

/**
 * This function should return the word at the top of the stack of the current
 * frame, interpreted as a signed integer.
 **/
word tos(ijvm* m);

/**
 * Step (perform) one instruction and return.
 * In the case of WIDE, perform the whole WIDE_ISTORE, WIDE_ILOAD or WIDE IINC.
 * If machine has halted or encountered an error, finished() should report
 * true afterward. 
 **/
void step(ijvm* m);


/**
 * Check whether the machine has any more instructions to execute.
 *
 * A machine will stop running after:
 * - reaching the end of the text section
 * - encountering either the HALT/ERR instructions
 * - encountering an invalid instruction
 */
bool finished(ijvm* m);



/**
 * @param i index of variable to obtain.
 * @return Returns the i:th local variable of the current frame.
 **/
word get_local_variable(ijvm* m, int i);

/**
 * @return The value of the current instruction represented as a byte.
 *
 * This should NOT increase the program counter.
 **/
byte get_instruction(ijvm* m);

/**
 * Initializes the IJVM with the binary file found at the provided argument using 
 * stdin as input and stdout as output 

 * Returns  - A pointer to an ijvm struct on success
 *          - NULL on failure
 **/
ijvm* init_ijvm_std(char *binary_path);

/**
 * Run the vm with the current state until the machine halts.
 **/
void run(ijvm* m);


// Below: methods needed for bonus assignments

// Only needed for Tailcall assignment: 
//
// Get some measure indicative of the (call)stack size
// If you have a single continous stack this can be
// the number of elements on the stack
// Or it can be for example be the number of frames on the stack
// We use this only to test stack depth when using tailcall is less
// then when using regular calls. 
int get_call_stack_size(ijvm* m);


// Only needed for garbage collection assignment
// Checks if reference is a freed heap cell
// If a heap cell is garbage, then after a garbage collection run
// this method must return true on a reference to that cell
//  *until* the next NEWARRAY instruction (which may reuse the reference)
//
bool is_heap_freed(ijvm* m,word reference);

#endif

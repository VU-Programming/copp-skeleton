#ifndef IJVM_H
#define IJVM_H

#include <stdio.h>  /* contains type FILE * */
#include <stdint.h>  /* contains exact integer types int32_t, uint8_t */
#include <stdbool.h> /* contains the boolean */

typedef uint8_t byte_t; /* raw memory will be typed as uint8 */
typedef int32_t word_t; /* the basic unit of the ijvm will be an int32 */

#define MAGIC_NUMBER 0x1DEADFAD

#define OP_BIPUSH         ((byte_t) 0x10)
#define OP_DUP            ((byte_t) 0x59)
#define OP_ERR            ((byte_t) 0xFE)
#define OP_GOTO           ((byte_t) 0xA7)
#define OP_HALT           ((byte_t) 0xFF)
#define OP_IADD           ((byte_t) 0x60)
#define OP_IAND           ((byte_t) 0x7E)
#define OP_IFEQ           ((byte_t) 0x99)
#define OP_IFLT           ((byte_t) 0x9B)
#define OP_IF_ICMPEQ      ((byte_t) 0x9F)
#define OP_IINC           ((byte_t) 0x84)
#define OP_ILOAD          ((byte_t) 0x15)
#define OP_IN             ((byte_t) 0xFC)
#define OP_INVOKEVIRTUAL  ((byte_t) 0xB6)
#define OP_IOR            ((byte_t) 0xB0)
#define OP_IRETURN        ((byte_t) 0xAC)
#define OP_ISTORE         ((byte_t) 0x36)
#define OP_ISUB           ((byte_t) 0x64)
#define OP_LDC_W          ((byte_t) 0x13)
#define OP_NOP            ((byte_t) 0x00)
#define OP_OUT            ((byte_t) 0xFD)
#define OP_POP            ((byte_t) 0x57)
#define OP_SWAP           ((byte_t) 0x5F)
#define OP_WIDE           ((byte_t) 0xC4)

// Bonus assignment instructions
#define OP_TAILCALL       ((byte_t) 0xCB)

#define OP_NEWARRAY       ((byte_t) 0xD1)
#define OP_IALOAD         ((byte_t) 0xD2)
#define OP_IASTORE        ((byte_t) 0xD3)

#define OP_GC             ((byte_t) 0xD4)

#define OP_NETBIND        ((byte_t) 0xE1)
#define OP_NETCONNECT     ((byte_t) 0xE2)
#define OP_NETIN          ((byte_t) 0xE3)
#define OP_NETOUT         ((byte_t) 0xE4)
#define OP_NETCLOSE       ((byte_t) 0xE5)
/**
 * DO NOT MODIFY THIS FILE.
 **/




/**
 * Sets the input of the IJVM instance to the provided file.
 **/
void set_input(FILE *fp);


/**
 * Sets the output of the IJVM instance to the provided file
 **/
void set_output(FILE *fp);


/**
 * Initializes the IJVM with the binary file found at the provided argument
 * Note. You need to be able to re-initialize the IJVM after it has been started.
 *
 * Returns  0 on success
 *         -1 on failure
 **/
int init_ijvm(char *binary_path);


/**
 * Destroys a vm, that is to say, free all memory associated with the machine
 * and allow for a new call to init_ijvm().
 */
void destroy_ijvm(void);

/**
 * Returns the currently loaded program text as a byte array.
 **/
byte_t *get_text(void);


/**
 * Returns the size of the currently loaded program text.
 **/
unsigned int get_text_size(void);

/**
 * @param i index of the constant to obtain
 * @return The constant at location i in the constant pool.
 **/
word_t get_constant(int i);


/**
 * Returns the value of the program counter (as an offset from the first instruction).
 **/
unsigned int get_program_counter(void);

/**
 * This function should return the word at the top of the stack of the current
 * frame, interpreted as a signed integer.
 **/
word_t tos(void);

/**
 * Step (perform) one instruction and return.
 * In the case of WIDE, perform the whole WIDE_ISTORE, WIDE_ILOAD or WIDE IINC.
 * If machine has halted or encountered an error, finished() should report
 * false afterward. 
 **/
void step(void);


/**
 * Check whether the machine has any more instructions to execute.
 *
 * A machine will stop running after:
 * - reaching the end of the text section
 * - encountering either the HALT/ERR instructions
 * - encountering an invalid instruction
 */
bool finished(void);


/**
 * Run the vm with the current state until the machine halts.
 **/
void run(void);

/**
 * @param i index of variable to obtain.
 * @return Returns the i:th local variable of the current frame.
 **/
word_t get_local_variable(int i);

/**
 * @return The value of the current instruction represented as a byte_t.
 *
 * This should NOT increase the program counter.
 **/
byte_t get_instruction(void);

// Below: methods needed for bonus assignments

// Only needed for Tailcall assignment: 
//
// Get some measure indicative of the (call)stack size
// If you have a single continous stack this can be
// the number of elements on the stack
// Or it can be for example be the number of frames on the stack
// We use this only to test stack depth when using tailcall is less
// then when using regular calls. 
// int get_call_stack_size(void);


// Only needed for garbage collection assignment
// Checks if reference is a freed heap cell
// If a heap cell is garbage, then after a garbage collection run
// this method must return true on a reference to that cell
//  *until* the next NEWARRAY instruction (which may reuse the reference)
//
// bool is_heap_freed(word_t reference);

#endif

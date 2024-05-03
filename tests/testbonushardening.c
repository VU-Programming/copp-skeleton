#include <stdio.h>
#include "../include/ijvm.h"
#include "testutil.h"

//!!! Tests that fail within init_ijvm will not call destroy_ijvm.
//!!! Ensure that the variables you set there are overwritten properly.

/**
 * If a file doesn't contain the magic number, the init function should return NULL
 */
void test_no_magic_number()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/no_magic_number.ijvm");
  assert(m == NULL);
}

/**
 * If the constant pool size is larger than the file itself, the init function should return NULL
 */
void test_constant_size_overflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/constant_size_overflow.ijvm");
  assert(m == NULL);
}

/**
 * If the text pool size is larger than the file itself, the init function should return NULL
 */
void test_text_size_overflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/text_size_overflow.ijvm");
  assert(m == NULL);
}

/**
 * If an invalid instruction is met, the IJVM should exit gracefully.
 */
void test_invalid_instruction()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/invalid_instruction.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * Tries to remove more values from the stack than there are.
 */
void test_underflow_stack()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/underflow_stack.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform a BIPUSH, but there's no argument.
 */
void test_no_arg_bipush()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/no_arg_bipush.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform DUP on an empty stack.
 */
void test_empty_stack_dup()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/empty_stack_dup.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform IADD on a single element.
 */
void test_single_element_iadd()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_iadd.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform IAND on a single element.
 */
void test_single_element_iand()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_iand.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform IOR on a single element.
 */
void test_single_element_ior()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_ior.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform ISUB on a single element.
 */
void test_single_element_isub()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_isub.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform SWAP on a single element.
 */
void test_single_element_swap()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_swap.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform a GOTO, but there's only one byte.
 */
void test_one_arg_goto()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_goto.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to GOTO outside of the text area.
 */
void test_goto_after()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/goto_after.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to GOTO outside of the text area.
 */
void test_goto_before()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/goto_before.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform a IFEQ, but there's only one byte.
 */
void test_one_arg_ifeq()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_ifeq.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFEQ outside of the text area.
 */
void test_ifeq_after()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/ifeq_after.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFEQ outside of the text area.
 */
void test_ifeq_before()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/ifeq_before.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFEQ on an empty stack.
 */
void test_empty_stack_ifeq()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/empty_stack_ifeq.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform a IFLT, but there's only one byte.
 */
void test_one_arg_iflt()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_iflt.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFLT outside of the text area.
 */
void test_iflt_after()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/iflt_after.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFLT outside of the text area.
 */
void test_iflt_before()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/iflt_before.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IFLT on an empty stack.
 */
void test_empty_stack_iflt()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/empty_stack_iflt.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform a IF_ICMPEQ, but there's only one byte.
 */
void test_one_arg_if_icmpeq()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_if_icmpeq.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IF_ICMPEQ outside of the text area.
 */
void test_if_icmpeq_after()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/if_icmpeq_after.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to IF_ICMPEQ outside of the text area.
 */
void test_if_icmpeq_before()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/if_icmpeq_before.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform IF_ICMPEQ on a single element.
 */
void test_single_element_if_icmpeq()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/single_element_if_icmpeq.ijvm");
  assert(m != NULL);

  step(m);
  assert(tos(m) == 0x1);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform LDC_W, but there's only one byte,
 */
void test_one_arg_ldc_w()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_ldc_w.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform LDC_W on a non-existent constant.
 */
void test_empty_constants_ldc_w()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/empty_constants_ldc_w.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform ILOAD, but there's no byte.
 */
void test_no_arg_iload()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/no_arg_iload.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform ISTORE, but there's no byte.
 */
void test_no_arg_istore()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/no_arg_istore.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform ISTORE on an empty stack.
 */
void test_empty_stack_istore()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/empty_stack_istore.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform IINC, but there's only one byte.
 */
void test_one_arg_iinc()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_iinc.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Tries to perform WIDE, but there's no instruction after.
 */
void test_no_instruction_wide()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/no_instruction_wide.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * If an invalid instruction is met after the WIDE instruction, the IJVM should exit gracefully.
 */
void test_invalid_wide_instruction()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/invalid_wide_instruction.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * Attempts to call INVOKEVIRTUAL, but there's only one byte.
 */
void test_one_arg_invokevirtual()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/one_arg_invokevirtual.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m)); //when an error occurs, the emulator should halt itself

  destroy_ijvm(m);
}

/**
 * Attempts to call INVOKEVIRTUAL, but the method reference does not exist in the constant pool.
 */
void test_invokevirtual_missing_constant()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/invokevirtual_missing_constant.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * Attempts to call INVOKEVIRTUAL, but the method reference does not exist in the text pool.
 */
void test_invokevirtual_invalid_constant()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/invokevirtual_invalid_constant.ijvm");
  assert(m != NULL);

  step(m);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * Attempts to call IRETURN when the stack is empty.
 */
void test_ireturn_empty_stack()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/ireturn_empty_stack.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * Attempts to call IRETURN when in main.
 */
void test_ireturn_main()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/ireturn_main.ijvm");
  assert(m != NULL);

  steps(m, 2);
  assert(finished(m));

  destroy_ijvm(m);
}

/**
 * IADD overflows.
 */
void test_iadd_overflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/iadd_overflow.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(tos(m) == -294967296);

  destroy_ijvm(m);
}

/**
 * IADD underflows.
 */
void test_iadd_underflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/iadd_underflow.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(tos(m) == 294967296);

  destroy_ijvm(m);
}

/**
 * ISUB overflows.
 */
void test_isub_overflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/isub_overflow.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(tos(m) == -294967296);

  destroy_ijvm(m);
}

/**
 * ISUB underflows.
 */
void test_isub_underflow()
{
  ijvm *m = init_ijvm_std("files/bonus/hardening/isub_underflow.ijvm");
  assert(m != NULL);

  steps(m, 3);
  assert(tos(m) == 294967296);

  destroy_ijvm(m);
}

int main()
{
  RUN_TEST(test_no_magic_number);
  RUN_TEST(test_constant_size_overflow);
  RUN_TEST(test_text_size_overflow);
  RUN_TEST(test_invalid_instruction);
  RUN_TEST(test_underflow_stack);
  RUN_TEST(test_empty_stack_dup);
  RUN_TEST(test_single_element_iadd);
  RUN_TEST(test_single_element_iand);
  RUN_TEST(test_single_element_ior);
  RUN_TEST(test_single_element_isub);
  RUN_TEST(test_single_element_swap);
  RUN_TEST(test_one_arg_goto);
  RUN_TEST(test_goto_after);
  RUN_TEST(test_goto_before);
  RUN_TEST(test_one_arg_ifeq);
  RUN_TEST(test_ifeq_after);
  RUN_TEST(test_ifeq_before);
  RUN_TEST(test_empty_stack_ifeq);
  RUN_TEST(test_one_arg_iflt);
  RUN_TEST(test_iflt_after);
  RUN_TEST(test_iflt_before);
  RUN_TEST(test_empty_stack_iflt);
  RUN_TEST(test_one_arg_if_icmpeq);
  RUN_TEST(test_if_icmpeq_after);
  RUN_TEST(test_if_icmpeq_before);
  RUN_TEST(test_single_element_if_icmpeq);
  RUN_TEST(test_one_arg_ldc_w);
  RUN_TEST(test_empty_constants_ldc_w);
  RUN_TEST(test_no_arg_iload);
  RUN_TEST(test_no_arg_istore);
  RUN_TEST(test_empty_stack_istore);
  RUN_TEST(test_one_arg_iinc);
  RUN_TEST(test_no_instruction_wide);
  RUN_TEST(test_invalid_wide_instruction);
  RUN_TEST(test_one_arg_invokevirtual);
  RUN_TEST(test_invokevirtual_missing_constant);
  RUN_TEST(test_invokevirtual_invalid_constant);
  RUN_TEST(test_ireturn_empty_stack);
  RUN_TEST(test_ireturn_main);
  RUN_TEST(test_iadd_overflow);
  RUN_TEST(test_iadd_underflow);
  RUN_TEST(test_isub_overflow);
  RUN_TEST(test_isub_underflow);
  return END_TEST();
}

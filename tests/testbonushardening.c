#include <stdio.h>
#include "../include/ijvm.h"
#include "testutil.h"

//!!! Tests that fail within init_ijvm will not call destroy_ijvm.
//!!! Ensure that the variables you set there are overwritten properly.

/**
 * If a file doesn't contain the magic number, the init function should return -1.
 */
void test_no_magic_number()
{
  int res = init_ijvm("files/bonus/hardening/no_magic_number.ijvm");
  assert(res == -1);
}

/**
 * If the constant pool size is larger than the file itself, the init function should return -1
 */
void test_constant_size_overflow()
{
  int res = init_ijvm("files/bonus/hardening/constant_size_overflow.ijvm");
  assert(res == -1);
}

/**
 * If the text pool size is larger than the file itself, the init function should return -1
 */
void test_text_size_overflow()
{
  int res = init_ijvm("files/bonus/hardening/text_size_overflow.ijvm");
  assert(res == -1);
}

/**
 * If an invalid instruction is met, the IJVM should exit gracefully.
 */
void test_invalid_instruction()
{
  int res = init_ijvm("files/bonus/hardening/invalid_instruction.ijvm");
  assert(res != -1);

  step();
  assert(finished());

  destroy_ijvm();
}

/**
 * Tries to remove more values from the stack than there are.
 */
void test_underflow_stack()
{
  int res = init_ijvm("files/bonus/hardening/underflow_stack.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform a BIPUSH, but there's no argument.
 */
void test_no_arg_bipush()
{
  int res = init_ijvm("files/bonus/hardening/no_arg_bipush.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform DUP on an empty stack.
 */
void test_empty_stack_dup()
{
  int res = init_ijvm("files/bonus/hardening/empty_stack_dup.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform IADD on a single element.
 */
void test_single_element_iadd()
{
  int res = init_ijvm("files/bonus/hardening/single_element_iadd.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform IAND on a single element.
 */
void test_single_element_iand()
{
  int res = init_ijvm("files/bonus/hardening/single_element_iand.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform IOR on a single element.
 */
void test_single_element_ior()
{
  int res = init_ijvm("files/bonus/hardening/single_element_ior.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform ISUB on a single element.
 */
void test_single_element_isub()
{
  int res = init_ijvm("files/bonus/hardening/single_element_isub.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform SWAP on a single element.
 */
void test_single_element_swap()
{
  int res = init_ijvm("files/bonus/hardening/single_element_swap.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform a GOTO, but there's only one byte.
 */
void test_one_arg_goto()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_goto.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to GOTO outside of the text area.
 */
void test_goto_after()
{
  int res = init_ijvm("files/bonus/hardening/goto_after.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to GOTO outside of the text area.
 */
void test_goto_before()
{
  int res = init_ijvm("files/bonus/hardening/goto_before.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform a IFEQ, but there's only one byte.
 */
void test_one_arg_ifeq()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_ifeq.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFEQ outside of the text area.
 */
void test_ifeq_after()
{
  int res = init_ijvm("files/bonus/hardening/ifeq_after.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFEQ outside of the text area.
 */
void test_ifeq_before()
{
  int res = init_ijvm("files/bonus/hardening/ifeq_before.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFEQ on an empty stack.
 */
void test_empty_stack_ifeq()
{
  int res = init_ijvm("files/bonus/hardening/empty_stack_ifeq.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform a IFLT, but there's only one byte.
 */
void test_one_arg_iflt()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_iflt.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFLT outside of the text area.
 */
void test_iflt_after()
{
  int res = init_ijvm("files/bonus/hardening/iflt_after.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFLT outside of the text area.
 */
void test_iflt_before()
{
  int res = init_ijvm("files/bonus/hardening/iflt_before.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IFLT on an empty stack.
 */
void test_empty_stack_iflt()
{
  int res = init_ijvm("files/bonus/hardening/empty_stack_iflt.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform a IF_ICMPEQ, but there's only one byte.
 */
void test_one_arg_if_icmpeq()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_if_icmpeq.ijvm");
  assert(res != -1);

  steps(3);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IF_ICMPEQ outside of the text area.
 */
void test_if_icmpeq_after()
{
  int res = init_ijvm("files/bonus/hardening/if_icmpeq_after.ijvm");
  assert(res != -1);

  steps(3);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to IF_ICMPEQ outside of the text area.
 */
void test_if_icmpeq_before()
{
  int res = init_ijvm("files/bonus/hardening/if_icmpeq_before.ijvm");
  assert(res != -1);

  steps(3);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform IF_ICMPEQ on a single element.
 */
void test_single_element_if_icmpeq()
{
  int res = init_ijvm("files/bonus/hardening/single_element_if_icmpeq.ijvm");
  assert(res != -1);

  step();
  assert(tos() == 0x1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform LDC_W, but there's only one byte,
 */
void test_one_arg_ldc_w()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_ldc_w.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform LDC_W on a non-existent constant.
 */
void test_empty_constants_ldc_w()
{
  int res = init_ijvm("files/bonus/hardening/empty_constants_ldc_w.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform ILOAD, but there's no byte.
 */
void test_no_arg_iload()
{
  int res = init_ijvm("files/bonus/hardening/no_arg_iload.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform ISTORE, but there's no byte.
 */
void test_no_arg_istore()
{
  int res = init_ijvm("files/bonus/hardening/no_arg_istore.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform ISTORE on an empty stack.
 */
void test_empty_stack_istore()
{
  int res = init_ijvm("files/bonus/hardening/empty_stack_istore.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform IINC, but there's only one byte.
 */
void test_one_arg_iinc()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_iinc.ijvm");
  assert(res != -1);

  steps(3);
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Tries to perform WIDE, but there's no instruction after.
 */
void test_no_instruction_wide()
{
  int res = init_ijvm("files/bonus/hardening/no_instruction_wide.ijvm");
  assert(res != -1);

  step();
  assert(finished());

  destroy_ijvm();
}

/**
 * If an invalid instruction is met after the WIDE instruction, the IJVM should exit gracefully.
 */
void test_invalid_wide_instruction()
{
  int res = init_ijvm("files/bonus/hardening/invalid_wide_instruction.ijvm");
  assert(res != -1);

  step();
  assert(finished());

  destroy_ijvm();
}

/**
 * Attempts to call INVOKEVIRTUAL, but there's only one byte.
 */
void test_one_arg_invokevirtual()
{
  int res = init_ijvm("files/bonus/hardening/one_arg_invokevirtual.ijvm");
  assert(res != -1);

  step();
  assert(finished()); //when an error occurs, the emulator should halt itself

  destroy_ijvm();
}

/**
 * Attempts to call INVOKEVIRTUAL, but the method reference does not exist in the constant pool.
 */
void test_invokevirtual_missing_constant()
{
  int res = init_ijvm("files/bonus/hardening/invokevirtual_missing_constant.ijvm");
  assert(res != -1);

  step();
  assert(finished());

  destroy_ijvm();
}

/**
 * Attempts to call INVOKEVIRTUAL, but the method reference does not exist in the text pool.
 */
void test_invokevirtual_invalid_constant()
{
  int res = init_ijvm("files/bonus/hardening/invokevirtual_invalid_constant.ijvm");
  assert(res != -1);

  step();
  assert(finished());

  destroy_ijvm();
}

/**
 * Attempts to call IRETURN when the stack is empty.
 */
void test_ireturn_empty_stack()
{
  int res = init_ijvm("files/bonus/hardening/ireturn_empty_stack.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished());

  destroy_ijvm();
}

/**
 * Attempts to call IRETURN when in main.
 */
void test_ireturn_main()
{
  int res = init_ijvm("files/bonus/hardening/ireturn_main.ijvm");
  assert(res != -1);

  steps(2);
  assert(finished());

  destroy_ijvm();
}

/**
 * IADD overflows.
 */
void test_iadd_overflow()
{
  int res = init_ijvm("files/bonus/hardening/iadd_overflow.ijvm");
  assert(res != -1);

  steps(3);
  assert(tos() == -294967296);

  destroy_ijvm();
}

/**
 * IADD underflows.
 */
void test_iadd_underflow()
{
  int res = init_ijvm("files/bonus/hardening/iadd_underflow.ijvm");
  assert(res != -1);

  steps(3);
  assert(tos() == 294967296);

  destroy_ijvm();
}

/**
 * ISUB overflows.
 */
void test_isub_overflow()
{
  int res = init_ijvm("files/bonus/hardening/isub_overflow.ijvm");
  assert(res != -1);

  steps(3);
  assert(tos() == -294967296);

  destroy_ijvm();
}

/**
 * ISUB underflows.
 */
void test_isub_underflow()
{
  int res = init_ijvm("files/bonus/hardening/isub_underflow.ijvm");
  assert(res != -1);

  steps(3);
  assert(tos() == 294967296);

  destroy_ijvm();
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

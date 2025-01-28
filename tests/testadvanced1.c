#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

/*****************************************************************************
 * testadvanced1: wide 
 *****************************************************************************
 * WIDE modifies ILOAD, ISTORE, IINC making the local variables short rather
 * than byte arguments.
 *
 * As mentioned in the method step(m), a step should execute both WIDE and
 * the next instruction in a single step.
 ****************************************************************************/

static FILE *tmp_out(void)
{
    FILE *output = fopen("tmp_output", "w+");
    assert(output);
    return output;
}

void test_wide1(void)
{
    FILE* output = tmp_out();
    ijvm* m = init_ijvm("files/advanced/test-wide1.ijvm",stdin,output);
    assert(m != NULL);

    steps(m, 6);
    assert(get_local_variable(m, 1) == 0x1);
    steps(m, 2);
    assert(get_local_variable(m, 257) == 0x2);
    step(m);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0x2);

    destroy_ijvm(m);
    fclose(output);
    remove("tmp_output");
}

void test_wide2(void)
{
    FILE* output = tmp_out();
    ijvm* m = init_ijvm("files/advanced/test-wide2.ijvm",stdin,output);
    assert(m != NULL);

    steps(m, 6);
    assert(get_local_variable(m, 1) == 0x1);
    steps(m, 2);
    assert(get_local_variable(m, 32768) == 0x2);
    step(m);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0x2);

    destroy_ijvm(m);
    fclose(output);
    remove("tmp_output");
}

void test_wide3(void)
{
    FILE* output = tmp_out();
    ijvm* m = init_ijvm("files/advanced/test-wide3.ijvm",stdin,output);
    assert(m != NULL);

    steps(m, 6);
    assert(get_local_variable(m, 1) == 0x1);
    steps(m, 2);
    assert(get_local_variable(m, 32768) == 0x2);
    steps(m, 3);
    assert(tos(m) == 0x5);
    step(m);
    assert(tos(m) == 0xa);

    destroy_ijvm(m);
    fclose(output);
    remove("tmp_output");
}

void test_wide4(void)
{
    FILE* output = tmp_out();
    ijvm* m = init_ijvm("files/advanced/test-wide4.ijvm",stdin,output);
    assert(m != NULL);

    word foo_const = 0xDEADBEEF;
    word bar_const = 0xABADBABE;


    while (OP_IRETURN != get_instruction(m))
        step(m);

    assert(get_local_variable(m, 1 + 0) == bar_const);
    assert(get_local_variable(m, 1 + 512) == bar_const);
    assert(get_local_variable(m, 1 + 1000) == bar_const);
    assert(get_local_variable(m, 1 + 1023) == bar_const);


    while (OP_IAND != get_instruction(m))
        step(m);

    assert(get_local_variable(m, 1 + 0) == foo_const);
    assert(get_local_variable(m, 1 + 512) == foo_const);
    assert(get_local_variable(m, 1 + 1000) == foo_const);
    assert(get_local_variable(m, 1 + 1023) == foo_const);

    destroy_ijvm(m);
    fclose(output);
    remove("tmp_output");
}

int main(void)
{
    fprintf(stderr, "*** testadvanced1: WIDE ......\n");
    RUN_TEST(test_wide1);
    RUN_TEST(test_wide2);
    RUN_TEST(test_wide3);
    RUN_TEST(test_wide4);
    return END_TEST();
}

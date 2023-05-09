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
 * As mentioned in the method step(), a step should execute both WIDE and
 * the next instruction in a single step.
 ****************************************************************************/

static FILE *ignore_stdout(void)
{
    FILE *output = fopen("tmp_output", "w+");
    assert(output);
    set_output(output);
    return output;
}

void test_wide1(void)
{
    int res = init_ijvm("files/advanced/test-wide1.ijvm");
    assert(res != -1);
    FILE *output = ignore_stdout();

    steps(6);
    assert(get_local_variable(1) == 0x1);
    steps(2);
    assert(get_local_variable(257) == 0x2);
    step();
    assert(tos() == 0x1);
    step();
    assert(tos() == 0x2);

    destroy_ijvm();
    fclose(output);
    remove("tmp_output");
}

void test_wide2(void)
{
    int res = init_ijvm("files/advanced/test-wide2.ijvm");
    assert(res != -1);
    FILE *output = ignore_stdout();

    steps(6);
    assert(get_local_variable(1) == 0x1);
    steps(2);
    assert(get_local_variable(32768) == 0x2);
    step();
    assert(tos() == 0x1);
    step();
    assert(tos() == 0x2);

    destroy_ijvm();
    fclose(output);
    remove("tmp_output");
}

void test_wide3(void)
{
    int res = init_ijvm("files/advanced/test-wide3.ijvm");
    assert(res != -1);
    FILE *output = ignore_stdout();

    steps(6);
    assert(get_local_variable(1) == 0x1);
    steps(2);
    assert(get_local_variable(32768) == 0x2);
    steps(3);
    assert(tos() == 0x5);
    step();
    assert(tos() == 0xa);

    destroy_ijvm();
    fclose(output);
    remove("tmp_output");
}

int main(void)
{
    fprintf(stderr, "*** testadvanced1: WIDE ......\n");
    RUN_TEST(test_wide1);
    RUN_TEST(test_wide2);
    RUN_TEST(test_wide3);
    return END_TEST();
}

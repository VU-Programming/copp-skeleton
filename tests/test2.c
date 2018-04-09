#include <assert.h>
#include <stdio.h>
#include "ijvm.h"
#include "testutil.h"

void test_simple_bipush()
{
    int res = init_ijvm("files/task2/TestBipush1.ijvm");
    assert(res != -1);

    step();
    assert(tos() == 42); // TOS is 42
    destroy_ijvm();
}

void test_signed_bipush()
{
    int res = init_ijvm("files/task2/TestBipush2.ijvm");
    assert(res != -1);

    step();
    assert(tos() == -42); // TOS is -42
    destroy_ijvm();
}

void test_simple_iadd()
{
    int res = init_ijvm("files/task2/TestIadd1.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    assert(tos() == 60); // TOS is 60
    destroy_ijvm();
}

void test_signed_iadd()
{
    int res = init_ijvm("files/task2/TestIadd2.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    assert(tos() == -60); // TOS is 60
    destroy_ijvm();
}

void test_simple_isub()
{
    int res = init_ijvm("files/task2/TestIsub1.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    assert(tos() == -10); // TOS is -10
    destroy_ijvm();
}

void test_signed_isub()
{
    int res = init_ijvm("files/task2/TestIsub2.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    assert(tos() == 10); // TOS is 10
    destroy_ijvm();
}

void test_simple_iand()
{
    int res = init_ijvm("files/task2/TestIAND1.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    step();
    step();
    assert(tos() == 1); // TOS is 1
    destroy_ijvm();
}

void test_simple_ior()
{
    int res = init_ijvm("files/task2/TestIOR1.ijvm");
    assert(res != -1);

    step();
    step();
    step();
    step();
    step();
    assert(tos() == 127); // TOS is 127
    destroy_ijvm();
}

void test_swap()
{
    int res = init_ijvm("files/task2/TestSwap1.ijvm");
    assert(res != -1);

    step();
    assert(tos() == 10);
    step();
    assert(tos() == 20);
    step();
    assert(tos() == 10);
    step();
    assert(tos() == 20);
    destroy_ijvm();
}

void test_simple_stack_operations()
{
    int res = init_ijvm("files/task2/TestPop1.ijvm");
    assert(res != -1);

    steps(3);
    assert(tos() == 10);
    steps(3);
    assert(tos() == 50);
    step();
    assert(tos() == 10);
    destroy_ijvm();
}

int main()
{
    test_simple_bipush();
    test_signed_bipush();
    test_simple_iadd();
    test_signed_iadd();
    test_simple_isub();
    test_signed_isub();
    test_simple_iand();
    test_simple_ior();
    test_swap();
    test_simple_stack_operations();
    printf("## PASSED ALL TESTS FOR TASK 2 ##\n");
    return 0;
}

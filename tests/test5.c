#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"

void test_invokenoargs()
{
    int res = init_ijvm("files/task5/TestInvokeNoArgs.ijvm");
    assert(res != -1);

    steps(2);
    assert(tos() == 0x42);
    steps(2);
    assert(tos() == 0x43);
    steps(2);
    assert(tos() == 0x43);

    destroy_ijvm();
}

void test_invoke1()
{
    int res = init_ijvm("files/task5/test-invokevirtual1.ijvm");
    assert(res != -1);

    steps(3);
    int pc = get_program_counter();
    step();
    assert(get_program_counter() != pc + 1);
    step();
    assert(tos() == 0x1);
    steps(2);

    destroy_ijvm();
}

void test_ireturn1()
{
    int res = init_ijvm("files/task5/test-invokevirtual1.ijvm");
    assert(res != -1);

    steps(6);
    assert(tos() == 0x1);
    step();
    assert(tos() == 0x2);

    destroy_ijvm();
}

void test_invoke2()
{
    int res = init_ijvm("files/task5/test-invokevirtual2.ijvm");
    assert(res != -1);

    steps(5);
    int pc = get_program_counter();
    step();
    assert(get_program_counter() != pc + 1);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x3);
    steps(3);

    destroy_ijvm();
}
void test_ireturn2()
{
    int res = init_ijvm("files/task5/test-invokevirtual2.ijvm");
    assert(res != -1);

    steps(10);
    assert(tos() == 0x5);
    step();
    assert(tos() == 0x2);

    destroy_ijvm();
}

int main()
{
    RUN_TEST(test_invokenoargs);
    RUN_TEST(test_invoke1);
    RUN_TEST(test_ireturn1);
    RUN_TEST(test_invoke2);
    RUN_TEST(test_ireturn2);
    return END_TEST();
}

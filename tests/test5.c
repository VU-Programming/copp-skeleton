#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_invokenoargs(void)
{
    ijvm* m = init_ijvm_std("files/task5/TestInvokeNoArgs.ijvm");
    assert(m != NULL);

    steps(m, 2);
    assert(tos(m) == 0x42);
    steps(m, 2);
    assert(tos(m) == 0x43);
    steps(m, 2);
    assert(tos(m) == 0x43);

    destroy_ijvm(m);
}

void test_invoke1(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-invokevirtual1.ijvm");
    assert(m != NULL);

    steps(m, 3);
    int pc = get_program_counter(m);
    step(m);
    assert(get_program_counter(m) != pc + 1);
    step(m);
    assert(tos(m) == 0x1);
    steps(m, 2);

    destroy_ijvm(m);
}

void test_ireturn1(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-invokevirtual1.ijvm");
    assert(m != NULL);

    steps(m, 6);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0x2);

    destroy_ijvm(m);
}

void test_invoke2(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-invokevirtual2.ijvm");
    assert(m != NULL);

    steps(m, 5);
    int pc = get_program_counter(m);
    step(m);
    assert(get_program_counter(m) != pc + 1); // did we go to method?
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x3);
    steps(m, 2);
    assert(tos(m) == 0x5);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x5);
    step(m);
    assert(tos(m) == 0x6);
    step(m);
    assert(tos(m) == 0x10);
    step(m);
    destroy_ijvm(m);
}

void test_ireturn2(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-invokevirtual2.ijvm");
    assert(m != NULL);

    steps(m, 10);
    assert(tos(m) == 0x5);
    step(m);
    assert(tos(m) == 0x2);

    destroy_ijvm(m);
}

void test_frame(void) 
{
    ijvm* m = init_ijvm_std("files/task5/testinvoke-frame.ijvm");
    assert(m != NULL);

    steps(m, 6);
    assert(get_local_variable(m, 0) == 0x4);
    step(m);
    assert(get_local_variable(m, 1) == 0x3);

    steps(m, 5);
    assert(get_local_variable(m, 1) == 0x2);
    assert(get_local_variable(m, 2) == 0x3);

    steps(m, 2);
    assert(tos(m) == 0x5);
    step(m);
    assert(tos(m) == 0x2);
    assert(get_local_variable(m, 0) == 0x4);
    assert(get_local_variable(m, 1) == 0x3);
    destroy_ijvm(m);
}


void test_nested_invoke_simple(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-nestedinvoke-simple.ijvm");
    assert(m != NULL);


    step(m);
    int main_pc = get_program_counter(m) + 3;
    step(m);

    assert(get_program_counter(m) != main_pc);
    step(m);
    assert(tos(m) != 0x9);
    int magic_pc = get_program_counter(m) + 3;
    step(m);
    assert(get_program_counter(m) != magic_pc);
    int addone_pc = get_program_counter(m) + 3;
    steps(m, 2);
    assert(get_program_counter(m) != addone_pc);
    assert(get_program_counter(m) == magic_pc);
    step(m);
    assert(get_program_counter(m) != magic_pc);
    assert(get_program_counter(m) == main_pc);

    destroy_ijvm(m);
}


void test_nested_invoke(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-nestedinvoke.ijvm");
    assert(m != NULL);

    steps(m, 8);
    assert(tos(m) == 0x6);
    step(m);
    assert(tos(m) == 0x9);
    step(m);
    assert(tos(m) == 0x9);
    step(m);
    assert(tos(m) != 0x9);
    step(m);
    assert(tos(m) == 0x9);
    step(m);

    step(m);
    assert(tos(m) == 0x9);
    step(m);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0xA);
    step(m);
    assert(tos(m) == 0xA);
    steps(m, 3);
    assert(tos(m) == 0xA);
    destroy_ijvm(m);

}




void test_nested_frame(void)
{
    ijvm* m = init_ijvm_std("files/task5/test-nestedinvoke-frame.ijvm");
    assert(m != NULL);

    steps(m, 7);
    assert(tos(m) == 0x5);
    assert(get_local_variable(m, 0) == 0x21);
    assert(get_local_variable(m, 1) == 0x2C);

    steps(m, 5);
    assert(tos(m) == 0x6);
    assert(get_local_variable(m, 1) == 0x1);
    assert(get_local_variable(m, 2) == 0x5);

    steps(m, 8);
    assert(tos(m) == 0xA);
    assert(get_local_variable(m, 1) == 9);

    steps(m, 3);
    assert(tos(m) == 0xA);
    assert(get_local_variable(m, 1) == 0x1);
    assert(get_local_variable(m, 2) == 0x5);

    steps(m, 2);
    assert(tos(m) == 0x10);
    assert(get_local_variable(m, 0) == 0x21);
    assert(get_local_variable(m, 1) == 0x2C);

    destroy_ijvm(m);
}


void test_recursion(void)
{
    ijvm* m = init_ijvm_std("files/task5/recursive_sum.ijvm");
    assert(m != NULL);


    while(get_instruction(m)!=OP_IAND){
        step(m);
    }
    assert(tos(m) == 5050);
    destroy_ijvm(m);
}

void test_fib(void)
{
    ijvm* m = init_ijvm_std("files/task5/fib.ijvm");
    assert(m != NULL);
    run(m);
    assert(get_local_variable(m, 0) == 10946);
    destroy_ijvm(m);
}


int main(void)
{
    fprintf(stderr, "*** test5: METHODS ...........\n");
    RUN_TEST(test_invokenoargs);
    RUN_TEST(test_invoke1);
    RUN_TEST(test_ireturn1);
    RUN_TEST(test_invoke2);
    RUN_TEST(test_ireturn2);
    RUN_TEST(test_frame);
    RUN_TEST(test_nested_invoke_simple);
    RUN_TEST(test_nested_invoke);
    RUN_TEST(test_nested_frame);
    RUN_TEST(test_fib);
    RUN_TEST(test_recursion);
    return END_TEST();
}

#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"



void test_simple_bipush(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestBipush1.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    assert(tos(m) == 42); 
    destroy_ijvm(m);
}

void test_signed_bipush(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestBipush2.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    assert(tos(m) == -42); 
    destroy_ijvm(m);
}

void test_simple_iadd(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIadd1.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 5);
    assert(tos(m) == 60); 
    destroy_ijvm(m);
}

void test_dup(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestDup.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 3);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 5);
    step(m);
    assert(get_program_counter(m) == 6);
    assert(tos(m) == 60); 
    destroy_ijvm(m);
}

void test_signed_iadd(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIadd2.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 5);
    assert(tos(m) == -60); 
    destroy_ijvm(m);
}


void test_simple_isub(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIsub1.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 5);
    assert(tos(m) == -10);
    destroy_ijvm(m);
}

void test_signed_isub(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIsub2.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 5);
    assert(tos(m) == 10); 
    destroy_ijvm(m);
}

void test_simple_iand(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIAND1.ijvm");
    assert(m != NULL);

    assert(get_program_counter(m) == 0);
    step(m);
    assert(get_program_counter(m) == 2);
    step(m);
    assert(get_program_counter(m) == 4);
    step(m);
    assert(get_program_counter(m) == 6);
    step(m);
    assert(get_program_counter(m) == 7);
    step(m);
    assert(get_program_counter(m) == 8);
    assert(tos(m) == 1); 
    destroy_ijvm(m);
}

void test_simple_ior(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestIOR1.ijvm");
    assert(m != NULL);

    step(m);
    step(m);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 127); 
    destroy_ijvm(m);
}


void test_simple_stack_operations(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestPop1.ijvm");
    assert(m != NULL);

    steps(m,3);
    assert(tos(m) == 10);
    steps(m,3);
    assert(tos(m) == 50);
    step(m);
    assert(tos(m) == 10);
    destroy_ijvm(m);
}


void test_swap(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestSwap1.ijvm");
    assert(m != NULL);

    step(m);
    assert(tos(m) == 10);
    step(m);
    assert(tos(m) == 20);
    step(m);
    assert(tos(m) == 10);
    step(m);
    assert(tos(m) == 20);
    destroy_ijvm(m);
}

void test_nop(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestNop.ijvm");
    assert(m != NULL);
    step(m);
    step(m);
    step(m);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 30); 
    destroy_ijvm(m);
}

void test_err(void)
{
    FILE *err = tmpfile();
    ijvm* m = init_ijvm("files/task2/TestErr.ijvm",stdin, err);
    assert(m != NULL);

    steps(m,3);
    assert(finished(m));

    char buf[128] = {0};
    rewind(err);
    fread(buf, 1, 32, err);
    // check for error message 
    assert(isprint(buf[0])); // check that a printable character was printed
    assert(buf[0] != ' '); // check that a non space is printed

    destroy_ijvm(m);
    fclose(err);
}

void test_halt(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestPop1.ijvm");
    assert(m != NULL);
    steps(m, 8);
    assert(!finished(m));
    step(m);
    assert(finished(m));
    destroy_ijvm(m);
}

void test_no_halt(void)
{
    ijvm* m = init_ijvm_std("files/task2/TestNoHalt.ijvm");
    assert(m != NULL);
    steps(m,10);
    assert(!finished(m));
    step(m);
    assert(finished(m));
    destroy_ijvm(m);
}

void test_in_out(void)
{
    FILE * input, * output;
    input  = fopen("tmp_input", "w+");
    output = fopen("tmp_output", "w+");
    fprintf(input, "%s", "ABCDE");
    rewind(input);

    ijvm* m = init_ijvm("files/task2/TestInOut.ijvm", input, output);
    assert(m != NULL);
    assert(m->in == input);
    assert(m->out == output);
    
    assert(!finished(m)); // did you reset ?

    run(m);

    char buf[128] = {0};
    rewind(output);
    fread(buf, 1, 5, output);
    buf[5] = 0;
    // in case something goes wrong,
    // you can print the 5 bytes of output with this
    // fprintf(stderr,"Output inout test: %s\n", buf)
    assert(strncmp(buf, "EDCBA", 5) == 0);
    fclose(input);
    fclose(output);
    remove("tmp_input");
    remove("tmp_output");
    destroy_ijvm(m);
}

int main(void)
{
    fprintf(stderr, "*** test2: STACK .............\n");
    RUN_TEST(test_simple_bipush);
    RUN_TEST(test_signed_bipush);
    RUN_TEST(test_simple_iadd);
    RUN_TEST(test_dup);
    RUN_TEST(test_signed_iadd);
    RUN_TEST(test_simple_isub);
    RUN_TEST(test_signed_isub);
    RUN_TEST(test_simple_iand);
    RUN_TEST(test_simple_ior);
    RUN_TEST(test_simple_stack_operations);
    RUN_TEST(test_swap);
    RUN_TEST(test_nop);
    RUN_TEST(test_err);
    RUN_TEST(test_halt);
    RUN_TEST(test_no_halt);
    RUN_TEST(test_in_out);
    return END_TEST();
}

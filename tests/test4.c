#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_ldcw1(void)
{
    ijvm* m = init_ijvm_std("files/task4/LoadTest1.ijvm");
    assert(m != NULL);

    step(m);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x3);

    destroy_ijvm(m);
}

void test_simple_load(void)
{
    ijvm* m = init_ijvm_std("files/task4/LoadTest2.ijvm");
    assert(m != NULL);

    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x1);
    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x3);
    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x3);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x1);
    step(m);
    step(m);
    step(m);
    assert(tos(m) == 0x2A);

    destroy_ijvm(m);
}

void test_complex_load(void)
{
    ijvm* m = init_ijvm_std("files/task4/LoadTest3.ijvm");
    assert(m != NULL);

    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x2);
    step(m);
    assert(tos(m) == 0x0);
    step(m);
    step(m);
    assert(tos(m) == 0x3);
    step(m);
    assert(tos(m) == 0x2A);
    step(m);
    assert(tos(m) == 0x0);
    step(m);
    assert(tos(m) == 0x3);
    step(m);
    assert(tos(m) == 0x4F);
    step(m);
    assert(tos(m) == 0x3);
    step(m);
    assert(tos(m) == 0x4B);
    step(m);
    assert(tos(m) == 0x3);
    destroy_ijvm(m);
}

#define LOADTEST4_OUTPUT "kjihgfedcbaabcd"
void test_iteration_load(void)
{
    FILE *output_file = tmpfile();
    char buf[128] = {0};

    ijvm* m = init_ijvm("files/task4/LoadTest4.ijvm",stdin, output_file);
    assert(m != NULL);

    run(m);

    rewind(output_file);
    fread(buf, 1, 127, output_file);
    assert(strncmp(buf, LOADTEST4_OUTPUT, strlen(LOADTEST4_OUTPUT) + 1) == 0);

    destroy_ijvm(m);
    fclose(output_file);
}

void test_iinc(void)
{
    ijvm* m = init_ijvm_std("files/task4/IINCTest.ijvm");
    assert(m != NULL);

    steps(m, 4);
    assert(get_local_variable(m, 0) == 0);
    assert(get_local_variable(m, 1) == 0);

    step(m);
    assert(get_local_variable(m, 0) == 0);
    step(m);
    assert(get_local_variable(m, 0) == 1);
    step(m);
    assert(get_local_variable(m, 0) == 4);

    step(m);
    assert(get_local_variable(m, 1) == 0);
    step(m);
    assert(get_local_variable(m, 1) == -1);
    step(m);
    assert(get_local_variable(m, 1) == -4);
    destroy_ijvm(m);
}

void test_loadstore(void)
{
    ijvm* m = init_ijvm_std("files/task4/LoadStoreTest.ijvm");
    assert(m != NULL);

    while(get_instruction(m) != OP_ILOAD){
        step(m);
    }
    step(m);
    assert(tos(m) == 3);
    step(m);
    assert(tos(m) == 2);
    step(m);
    assert(tos(m) == 1);

    while(get_instruction(m) != OP_ILOAD){
        step(m);
    }
    step(m);
    assert(tos(m) == 4);
    step(m);
    assert(tos(m) == 5);
    step(m);
    assert(tos(m) == 6);

    destroy_ijvm(m);
}


void test_wide(void)
{
    ijvm* m = init_ijvm_std("files/task4/WIDETest.ijvm");
    assert(m != NULL);

    steps(m, 4);
    assert(get_local_variable(m, 0) == 3);
    assert(get_local_variable(m, 1) == 2);

    step(m);
    assert(get_local_variable(m, 0) == 6);
    step(m);
    assert(get_local_variable(m, 1) == -1);
    steps(m, 2);
    assert(tos(m) == 3);
    step(m);
    assert(tos(m) == 6);
    destroy_ijvm(m);
}

void test_wide_alternate(void)
{
    ijvm* m = init_ijvm_std("files/task4/WIDEAlternateTest.ijvm");
    assert(m != NULL);


    steps(m, 4);
    assert(get_local_variable(m, 0) == 3);
    assert(get_local_variable(m, 1) == 2);

    step(m);
    assert(get_local_variable(m, 0) == 6);
    step(m);
    assert(get_local_variable(m, 1) == -1);
    steps(m, 2);
    assert(tos(m) == 3);
    step(m);
    assert(tos(m) == 6);
    destroy_ijvm(m);
}

void test_wide_check(void)
{
    ijvm* m = init_ijvm_std("files/task4/WIDECheckTest.ijvm");
    assert(m != NULL);

    steps(m, 3);
    assert(tos(m) == -60);
    step(m);
    assert(get_local_variable(m, 0) == -60);
    step(m);
    assert(get_local_variable(m, 1) == -60);
    steps(m, 2);
    assert(get_local_variable(m, 0) == -57);
    step(m);
    assert(get_local_variable(m, 1) == -26);
    steps(m, 2);
    assert(tos(m) == -26);
    step(m);
    assert(tos(m) == -57);
    assert(!finished(m));
    step(m);
    assert(finished(m));
    destroy_ijvm(m);
}

int main(void)
{
    fprintf(stderr, "*** test4: VARS ..............\n");
    RUN_TEST(test_ldcw1);
    RUN_TEST(test_simple_load);
    RUN_TEST(test_complex_load);
    RUN_TEST(test_iteration_load);

    RUN_TEST(test_iinc);
    RUN_TEST(test_loadstore);

    RUN_TEST(test_wide);
    RUN_TEST(test_wide_alternate);
    RUN_TEST(test_wide_check); 
    return END_TEST();
}

#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"

void test_ldcw1()
{
    int res = init_ijvm("files/task4/LoadTest1.ijvm");
    assert(res != -1);

    step();
    assert(tos() == 0x1);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x3);

    destroy_ijvm();
}

void test_simple_load()
{
    int res = init_ijvm("files/task4/LoadTest3.ijvm");
    assert(res != -1);

    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x1);
    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x3);
    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x3);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x1);
    step();
    step();
    step();
    assert(tos() == 0x2A);

    destroy_ijvm();
}

void test_complex_load()
{
    int res = init_ijvm("files/task4/LoadTest2.ijvm");
    assert(res != -1);

    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x2);
    step();
    assert(tos() == 0x0);
    step();
    step();
    assert(tos() == 0x3);
    step();
    assert(tos() == 0x2A);
    step();
    assert(tos() == 0x0);
    step();
    assert(tos() == 0x3);
    step();
    assert(tos() == 0x4F);
    step();
    assert(tos() == 0x3);
    step();
    assert(tos() == 0x4B);
    step();
    assert(tos() == 0x3);
    destroy_ijvm();
}

#define LOADTEST4_OUTPUT "kjihgfedcbaabcd"
void test_iteration_load()
{
    FILE *output_file;
    char buf[128] = {0};

    int res = init_ijvm("files/task4/LoadTest4.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    run();

    rewind(output_file);
    fread(buf, 1, 127, output_file);
    assert(strncmp(buf, LOADTEST4_OUTPUT, strlen(LOADTEST4_OUTPUT) + 1) == 0);

    destroy_ijvm();
    fclose(output_file);
}

void test_iinc()
{
    int res = init_ijvm("files/task4/IINCTest.ijvm");
    assert(res != -1);

    steps(4);
    assert(get_local_variable(0) == 0);
    assert(get_local_variable(1) == 0);

    step();
    assert(get_local_variable(0) == 0);
    step();
    assert(get_local_variable(0) == 1);
    step();
    assert(get_local_variable(0) == 4);

    step();
    assert(get_local_variable(1) == 0);
    step();
    assert(get_local_variable(1) == -1);
    step();
    assert(get_local_variable(1) == -4);
    destroy_ijvm();
}


int main()
{
    RUN_TEST(test_ldcw1);
    RUN_TEST(test_simple_load);
    RUN_TEST(test_complex_load);
    RUN_TEST(test_iteration_load);
    RUN_TEST(test_iinc);
    return END_TEST();
}

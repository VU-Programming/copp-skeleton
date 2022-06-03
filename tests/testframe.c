#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"

void test_frame() {
    int res = init_ijvm("files/task5/testinvoke-frame.ijvm");
    assert(res != -1);

    steps(6);
    assert(get_local_variable(0) == 0x4);
    step();
    assert(get_local_variable(1) == 0x3);

    steps(5);
    assert(get_local_variable(1) == 0x2);
    assert(get_local_variable(2) == 0x3);

    steps(2);
    assert(tos() == 0x5);
    step();
    assert(tos() == 0x2);
    assert(get_local_variable(0) == 0x4);
    assert(get_local_variable(1) == 0x3);
    destroy_ijvm();
}

void test_nested_frame()
{
    int res = init_ijvm("files/advanced/test-nestedinvoke-frame.ijvm");
    assert(res != -1);

    steps(7);
    assert(tos() == 0x5);
    assert(get_local_variable(0) == 0x21);
    assert(get_local_variable(1) == 0x2C);

    steps(5);
    assert(tos() == 0x6);
    assert(get_local_variable(1) == 0x1);
    assert(get_local_variable(2) == 0x5);

    steps(8);
    assert(tos() == 0xA);
    assert(get_local_variable(1) == 9);

    steps(3);
    assert(tos() == 0xA);
    assert(get_local_variable(1) == 0x1);
    assert(get_local_variable(2) == 0x5);

    steps(2);
    assert(tos() == 0x10);
    assert(get_local_variable(0) == 0x21);
    assert(get_local_variable(1) == 0x2C);

    destroy_ijvm();
}



int main()
{
    RUN_TEST(test_frame);
    RUN_TEST(test_nested_frame);
    return END_TEST();
}

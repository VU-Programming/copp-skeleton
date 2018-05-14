#include <stdio.h>
#include "ijvm.h"
#include "testutil.h"

void test_program_1()
{
    int res = init_ijvm("files/task1/program1.ijvm");
    assert(res != -1);
    assert(text_size() == 7);
    byte_t *ip = get_text();

    // Instructions in binary
    assert(ip[0] == 0x10); // BIPUSH
    assert(ip[2] == 0x10); // BIPUSH
    assert(ip[4] == 0x60); // IADD
    assert(ip[5] == (byte_t)0xFD); // OUT
    destroy_ijvm();
}

void test_program_2()
{
    int res = init_ijvm("files/task1/program2.ijvm");
    assert(res != -1);
    assert(text_size() == 16);
    byte_t *ip = get_text();

    // Instructions in binary
    assert(ip[0] == 0x00);
    assert(ip[1] == (byte_t)0x13);
    assert(ip[4] == (byte_t)0x59);
    assert(ip[5] == (byte_t)0x13);
    assert(ip[8] == (byte_t)0x60);
    assert(ip[9] == (byte_t)0x13);
    assert(ip[12] == (byte_t)0x60);
    assert(ip[13] == (byte_t)0xFD);
    assert(ip[14] == (byte_t)0x00);
    destroy_ijvm();
}

void test_program_counter()
{
    int res = init_ijvm("files/task1/program1.ijvm");
    assert(res != -1);

    // PC should be initialized to 0
    assert(get_program_counter() == 0);
    destroy_ijvm();
}


int main()
{
    RUN_TEST(test_program_counter);
    RUN_TEST(test_program_1);
    RUN_TEST(test_program_2);
    return END_TEST();
}

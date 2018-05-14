#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"

void test_nested_invoke_simple()
{
    int res = init_ijvm("files/advanced/test-nestedinvoke-simple.ijvm");
    assert(res != -1);

    step();
    int main_pc = get_program_counter() + 3;
    step();

    assert(get_program_counter() != main_pc);
    step();
    assert(tos() != 0x9);
    int magic_pc = get_program_counter() + 3;
    step();
    assert(get_program_counter() != magic_pc);
    int addone_pc = get_program_counter() + 3;
    steps(2);
    assert(get_program_counter() != addone_pc);
    assert(get_program_counter() == magic_pc);
    step();
    assert(get_program_counter() != magic_pc);
    assert(get_program_counter() == main_pc);

    destroy_ijvm();
}

void test_nested_invoke()
{

    int res = init_ijvm("files/advanced/test-nestedinvoke.ijvm");
    assert(res != -1);

    steps(8);
    assert(tos() == 0x6);
    step();
    assert(tos() == 0x9);
    step();
    assert(tos() == 0x9);
    step();
    assert(tos() != 0x9);
    step();
    assert(tos() == 0x9);
    step();

    step();
    assert(tos() == 0x9);
    step();
    assert(tos() == 0x1);
    step();
    assert(tos() == 0xA);
    step();
    assert(tos() == 0xA);
    steps(3);
    assert(tos() == 0xA);
    destroy_ijvm();

}



int main()
{
    RUN_TEST(test_nested_invoke_simple);
    RUN_TEST(test_nested_invoke);
    return END_TEST();
}

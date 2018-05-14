#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"


void test_stack_100()
{
    int res = init_ijvm("files/advanced/teststack.ijvm");
    assert(res != -1);

    step();
    steps(2 * 100);
    assert(tos() == 0x2);

    destroy_ijvm();
}

void test_stack_3000()
{
    int res = init_ijvm("files/advanced/teststack.ijvm");
    assert(res != -1);

    step();
    steps(2 * 3000);
    assert(tos() == 0x2);

    destroy_ijvm();
}

void test_stack_50000()
{
    int res = init_ijvm("files/advanced/teststack.ijvm");
    assert(res != -1);

    step();
    steps(2 * 50000);
    assert(tos() == 0x2);

    destroy_ijvm();
}

void test_get_stack_contents()
{
    int res = init_ijvm("files/advanced/teststack.ijvm");
    assert(res != -1);

    step();
    steps(2*100);
    int size = stack_size();
    assert(size >= 100);
    word_t *stack = get_stack();
    int markers = 0;
    for (int i = 0; i < size; i++) {
        if (stack[i] == 0x2)
            markers++;
    }

    assert(markers >= 99);
    destroy_ijvm();

}

void test_method_stack()
{
    int res = init_ijvm("files/advanced/teststack2.ijvm");
    assert(res != -1);

    steps(8);
    int size1 = stack_size();
    word_t *stack1 = get_stack();
    int markers1 = 0;
    for (int i = 0; i < size1; i++) {
        if (stack1[i] == 0x2)
            markers1++;
    }
    assert(markers1 == 4);

    step();
    steps(2 * 5000);
    int size2 = stack_size();
    word_t *stack2 = get_stack();
    int markers2 = 0;
    for (int i = 0; i < size2; i++) {
        if (stack2[i] == 0x2)
            markers2++;
    }
    assert(markers2 > 4000);


    destroy_ijvm();

}
int main()
{
    RUN_TEST(test_stack_100);
    RUN_TEST(test_stack_3000);
    RUN_TEST(test_stack_50000);
    RUN_TEST(test_get_stack_contents);
    RUN_TEST(test_method_stack);
    return END_TEST();
}

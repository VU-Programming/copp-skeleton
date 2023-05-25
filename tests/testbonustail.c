#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_tailfib(void)
{
    int res = init_ijvm("files/bonus/tailfib.ijvm");
    assert(res != -1);
    run();
    assert(get_local_variable(0) == 433494437);
    destroy_ijvm();
}


void testTC(void) {
    FILE* output_file;
    int res = init_ijvm("files/bonus/test_tailcall.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);
    // run until returning from innermost call
    steps(129998);
    assert(tos() == 50005000);
    int stack1 = get_call_stack_size();
    run();
    assert(tos() == 50005000);


    destroy_ijvm();
    fclose(output_file);

    res = init_ijvm("files/bonus/test_taillesscall.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

   // run until returning from innermost call
    steps(129998);
    assert(tos() == 50005000);
    int stack2 = get_call_stack_size();
    run();
    assert(tos() == 50005000);


    destroy_ijvm();
    fclose(output_file);

    assert(stack1 < stack2);
    printf("Tailcall Stack: %d vs Invokevirtual Stack: %d\n", stack1, stack2);
}


int main(void)
{
    RUN_TEST(test_tailfib);
    RUN_TEST(testTC);
    return END_TEST();
}

#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

void test_tailfib(void)
{
    ijvm *m = init_ijvm_std("files/bonus/tailfib.ijvm");
    assert(m != NULL);
    run(m);
    assert(get_local_variable(m, 0) == 433494437);
    destroy_ijvm(m);
}


void testTC(void)
{
    FILE* output_file = tmpfile();
    ijvm *m = init_ijvm("files/bonus/test_tailcall.ijvm",stdin,output_file);
    assert(m != NULL);
    // run until returning from innermost call
    steps(m, 129998);
    assert(tos(m) == 50005000);
    int stack1 = get_call_stack_size(m);
    run(m);
    assert(tos(m) == 50005000);


    destroy_ijvm(m);
    fclose(output_file);

    output_file = tmpfile();
    m = init_ijvm("files/bonus/test_taillesscall.ijvm",stdin,output_file);
    assert(m != NULL);



   // run until returning from innermost call
    steps(m, 129998);
    assert(tos(m) == 50005000);
    int stack2 = get_call_stack_size(m);
    run(m);
    assert(tos(m) == 50005000);


    destroy_ijvm(m);
    fclose(output_file);

    assert(stack1 < stack2);
    printf("Tailcall Stack: %d vs Invokevirtual Stack: %d\n", stack1, stack2);
}

void test_out_of_memory(void)
{
    FILE* output_file = tmpfile();
    ijvm *m = init_ijvm("files/bonus/test_deep_tailcall.ijvm",stdin,output_file);
    assert(m != NULL);

    // if you don't free resources in tailcall, you'll get an OOM kill
    run(m);

    destroy_ijvm(m);
    fclose(output_file);
}

int main(void)
{
    RUN_TEST(test_tailfib);
    RUN_TEST(testTC);
    RUN_TEST(test_out_of_memory);
    return END_TEST();
}

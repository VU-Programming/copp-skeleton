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

int main(void)
{
    RUN_TEST(test_tailfib);
    return END_TEST();
}

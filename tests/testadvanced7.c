#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"
#define VAL 131072
// sum of 1 to val
#define SUM  (VAL * (VAL + 1) / 2) 

/* testadvanced7: tallstack */

void test_tallstack() {
    int res = init_ijvm("files/advanced/tallstack.ijvm");
    assert(res != -1);
    while(get_instruction()!=OP_IAND){
        step();
    }
    assert(tos() == SUM)

    destroy_ijvm();
}

void test_deep_recursion() {
    int res = init_ijvm("files/advanced/deep_recursion.ijvm");
    assert(res != -1);
    while(get_instruction()!=OP_IAND){
        step();
    }
    assert(tos() == SUM);
    destroy_ijvm();
}

int main()
{
    fprintf(stderr, "*** testadvanced7: TALL_STACK ...\n");
    RUN_TEST(test_tallstack);
    RUN_TEST(test_deep_recursion);
    return END_TEST();
}

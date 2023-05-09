#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"
#define VAL 65534
// sum of 1 to val, can be computed by (VAL * (VAL + 1) / 2) (but this overflows 32 bit)
#define SUM  2147385345 

/* testadvanced7: tallstack */

void test_tallstack(void) 
{
    int res = init_ijvm("files/advanced/tallstack.ijvm");
    assert(res != -1);
    while(get_instruction()!=OP_IAND){
        step();
    }
    assert(tos() == SUM)

    destroy_ijvm();
}

void test_deep_recursion(void) 
{
    int res = init_ijvm("files/advanced/deep_recursion.ijvm");
    assert(res != -1);
    while(get_instruction()!=OP_IAND){
        step();
    }
    assert(tos() == SUM);

    destroy_ijvm();
}

int main(void)
{
    fprintf(stderr, "*** testadvanced7: TALL_STACK ...\n");
    RUN_TEST(test_tallstack);
    RUN_TEST(test_deep_recursion);
    return END_TEST();
}

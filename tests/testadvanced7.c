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
    ijvm *m = init_ijvm_std("files/advanced/tallstack.ijvm");
    assert(m != NULL);
    while(get_instruction(m)!=OP_IAND){
        step(m);
    }
    assert(tos(m) == SUM)

    destroy_ijvm(m);
}

void test_deep_recursion(void) 
{
    ijvm *m = init_ijvm_std("files/advanced/deep_recursion.ijvm");
    assert(m != NULL);

    while(get_instruction(m)!=OP_IAND){
        step(m);
    }
    assert(tos(m) == SUM);

    destroy_ijvm(m);
}

int main(void)
{
    fprintf(stderr, "*** testadvanced7: TALL_STACK ...\n");
    RUN_TEST(test_tallstack);
    RUN_TEST(test_deep_recursion);
    return END_TEST();
}

#include "../include/ijvm.h"
#include <stdlib.h>

#include "testutil.h"

/* testing GC doesn't free used space */
void testGC1(void) {
    FILE* output_file;
    int res = init_ijvm("files/bonus/TestGC1.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    step();
    assert(tos() == 32);
    step();
    word_t reference = tos();
    steps(2);
    assert(get_local_variable(0) == reference);
    steps(4);
    assert(tos() == reference);
    steps(4);
    step();
    assert(tos() == 18);
    assert(!is_heap_freed(reference));
    steps(2);

    destroy_ijvm();
    fclose(output_file);
}

/*  testing that GC does free unused space. In this test:
    - while in a method it shouldn't be freed
    - after returning from a method, array 2 should be freed
    - after replacing array 1 with something other than ref1, array 1 should be freed
*/
void testGC2(void) {
    FILE* output_file;
    int res = init_ijvm("files/bonus/TestGC2.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    step();
    assert(tos() == 32);
    step();
    word_t ref1 = tos();
    steps(2);
    assert(get_local_variable(0) == ref1);
    steps(4);
    assert(tos() == ref1);
    steps(4);
    step();
    assert(tos() == 18);
    steps(5);
    assert(tos() == 64);
    step();
    word_t ref2 = tos();
    steps(2);
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    steps(3);
    assert(tos() == ref2);
    steps(2);
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    steps(3);
    assert(tos() == 34);
    step();
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    step();
    assert(tos() == 34);
    step();
    assert(!is_heap_freed(ref1));
    assert(is_heap_freed(ref2));
    steps(4);
    assert(is_heap_freed(ref1));
    assert(is_heap_freed(ref2));
    step();

    destroy_ijvm();
    fclose(output_file);
}

/* proves that GC checks non-freed heaps for reference */
void testGC3(void) {
    FILE* output_file;
    int res = init_ijvm("files/bonus/TestGC3.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    step();
    assert(tos() == 32);
    step();
    word_t ref1 = tos();
    steps(2);
    assert(get_local_variable(0) == ref1);
    steps(4);
    assert(tos() == ref1);
    steps(4);
    step();
    assert(tos() == 18);
    steps(5);
    assert(tos() == 64);
    step();
    word_t ref2 = tos();
    steps(2);
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    steps(3);
    assert(tos() == ref2);
    steps(2);
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    steps(3);
    assert(tos() == 34);
    step();
    assert(!is_heap_freed(ref1));
    assert(!is_heap_freed(ref2));
    step();
    assert(tos() == 34);
    step();
    assert(!is_heap_freed(ref1));
    assert(is_heap_freed(ref2));

    steps(3);
    word_t ref3 = tos();
    steps(10);
    assert(!is_heap_freed(ref3));
    steps(5);
    assert(tos() == 50);
    step();
    assert(!is_heap_freed(ref3));
    steps(4);
    assert(is_heap_freed(ref3));
    assert(!is_heap_freed(ref1));

    steps(3);
    assert(is_heap_freed(ref1));
    assert(is_heap_freed(ref2));
    assert(is_heap_freed(ref3));
    step();

    destroy_ijvm();
    fclose(output_file);
}

/* testing that GC removes heaps with only cyclic references */
void testGC4(void) {
    FILE* output_file;
    int res = init_ijvm("files/bonus/TestGC4.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    step();
    assert(tos() == 32);
    step();
    word_t reference1 = tos();
    steps(2);
    assert(get_local_variable(0) == reference1);
    
    steps(2);
    assert(tos() == 64);
    step();
    word_t reference2 = tos();
    steps(2);
    assert(get_local_variable(1) == reference2);

    steps(9);
    assert(!is_heap_freed(reference1));
    assert(!is_heap_freed(reference2));
    steps(2);
    assert(tos() == 1);
    steps(2);
    assert(!is_heap_freed(reference1));
    assert(!is_heap_freed(reference2));
    step();
    assert(tos() == 1);
    steps(2);
    assert(is_heap_freed(reference1));
    assert(is_heap_freed(reference2));
    step();

    destroy_ijvm();
    fclose(output_file);
}

int main(void) {
    RUN_TEST(testGC1);
    RUN_TEST(testGC2);
    RUN_TEST(testGC3);
    RUN_TEST(testGC4);
    return END_TEST();
}

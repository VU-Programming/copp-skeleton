#include "../include/ijvm.h"
#include <stdlib.h>

#include "testutil.h"

/* testing GC doesn't free used space */
void testGC1(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestGC1.ijvm", stdin, output_file);
	assert(m != NULL);

    step(m);
    assert(tos(m) == 32);
    step(m);
    word reference = tos(m);
    steps(m, 2);
    assert(get_local_variable(m, 0) == reference);
    steps(m, 4);
    assert(tos(m) == reference);
    steps(m, 4);
    step(m);
    assert(tos(m) == 18);
    assert(!is_heap_freed(m, reference));
    steps(m, 2);

	destroy_ijvm(m);
	fclose(output_file);
}

/*  testing that GC does free unused space. In this test:
    - while in a method it shouldn't be freed
    - after returning from a method, array 2 should be freed
    - after replacing array 1 with something other than ref1, array 1 should be freed
*/
void testGC2(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestGC2.ijvm", stdin, output_file);
	assert(m != NULL);

    step(m);
    assert(tos(m) == 32);
    step(m);
    word ref1 = tos(m);
    steps(m, 2);
    assert(get_local_variable(m, 0) == ref1);
    steps(m, 4);
    assert(tos(m) == ref1);
    steps(m, 4);
    step(m);
    assert(tos(m) == 18);
    steps(m, 5);
    assert(tos(m) == 64);
    step(m);
    word ref2 = tos(m);
    steps(m, 2);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    steps(m, 3);
    assert(tos(m) == ref2);
    steps(m, 2);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    steps(m, 3);
    assert(tos(m) == 34);
    step(m);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    step(m);
    assert(tos(m) == 34);
    step(m);
    assert(!is_heap_freed(m,ref1));
    assert(is_heap_freed(m,ref2));
    steps(m, 4);
    assert(is_heap_freed(m,ref1));
    assert(is_heap_freed(m,ref2));
    step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

/* proves that GC checks non-freed heaps for reference */
void testGC3(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestGC3.ijvm", stdin, output_file);
	assert(m != NULL);

    step(m);
    assert(tos(m) == 32);
    step(m);
    word ref1 = tos(m);
    steps(m, 2);
    assert(get_local_variable(m, 0) == ref1);
    steps(m, 4);
    assert(tos(m) == ref1);
    steps(m, 4);
    step(m);
    assert(tos(m) == 18);
    steps(m, 5);
    assert(tos(m) == 64);
    step(m);
    word ref2 = tos(m);
    steps(m, 2);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    steps(m, 3);
    assert(tos(m) == ref2);
    steps(m, 2);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    steps(m, 3);
    assert(tos(m) == 34);
    step(m);
    assert(!is_heap_freed(m,ref1));
    assert(!is_heap_freed(m,ref2));
    step(m);
    assert(tos(m) == 34);
    step(m);
    assert(!is_heap_freed(m,ref1));
    assert(is_heap_freed(m,ref2));

    steps(m, 3);
    word ref3 = tos(m);
    steps(m, 10);
    assert(!is_heap_freed(m,ref3));
    steps(m, 5);
    assert(tos(m) == 50);
    step(m);
    assert(!is_heap_freed(m,ref3));
    steps(m, 4);
    assert(is_heap_freed(m,ref3));
    assert(!is_heap_freed(m,ref1));

	steps(m, 3);
	assert(is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	assert(is_heap_freed(m, ref3));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

/* testing that GC removes heaps with only cyclic references */
void testGC4(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestGC4.ijvm", stdin, output_file);
	assert(m != NULL);

    step(m);
    assert(tos(m) == 32);
    step(m);
    word reference1 = tos(m);
    steps(m, 2);
    assert(get_local_variable(m, 0) == reference1);
    
    steps(m, 2);
    assert(tos(m) == 64);
    step(m);
    word reference2 = tos(m);
    steps(m, 2);
    assert(get_local_variable(m, 1) == reference2);

	steps(m, 9);
	assert(!is_heap_freed(m, reference1));
	assert(!is_heap_freed(m, reference2));
	steps(m, 2);
	assert(tos(m) == 1);
	steps(m, 2);
	assert(!is_heap_freed(m, reference1));
	assert(!is_heap_freed(m, reference2));
	step(m);
	assert(tos(m) == 1);
	steps(m, 2);
	assert(is_heap_freed(m, reference1));
	assert(is_heap_freed(m, reference2));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

int main(void) {
	RUN_TEST(testGC1);
	RUN_TEST(testGC2);
	RUN_TEST(testGC3);
	RUN_TEST(testGC4);
	return END_TEST();
}

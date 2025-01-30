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
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 3);
	assert(tos(m) == ref2);
	steps(m, 2);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 3);
	assert(tos(m) == 34);
	step(m);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	step(m);
	assert(tos(m) == 34);
	step(m);
	assert(!is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	steps(m, 4);
	assert(is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

/* proves that GC checks non-freed heaps for reference */
void testGC3(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestAltGC3.ijvm", stdin, output_file);
	assert(m != NULL);

	step(m);
	assert(tos(m) == 32);
	step(m);
	word ref1 = tos(m);
	steps(m, 2);
	assert(get_local_variable(m, 0) == ref1);
	step(m);
	assert(!is_heap_freed(m, ref1));
	steps(m, 2);
	word ref2 = tos(m);
	steps(m, 6);
	assert(tos(m) == ref2);
	step(m);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 4);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 7);
	assert(tos(m) == 18);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));

	steps(m, 2);
	assert(is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

/* testing that GC removes heaps with only cyclic references and doesn't hang on an active cyclic reference */
void testGC4(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestAltGC4.ijvm", stdin, output_file);
	assert(m != NULL);

	step(m);
	assert(tos(m) == 32);
	step(m);
	word ref1 = tos(m);
	steps(m, 3);
	assert(get_local_variable(m, 0) == ref1);
	assert(!is_heap_freed(m, ref1));
	steps(m, 2);
	word ref2 = tos(m);
	steps(m, 11);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 3);
	assert(is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

/* tests if methods can return references without them being freed */
void testGC5(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestAltGC5.ijvm", stdin, output_file);
	assert(m != NULL);

	steps(m, 2);
	assert(tos(m) == 32);
	step(m);
	word ref1 = tos(m);
	steps(m, 9);
	assert(!is_heap_freed(m, ref1));
	step(m);
	assert(tos(m) == 8);
	step(m);
	word ref2 = tos(m);
	steps(m, 7);
	assert(tos(m) == ref2);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	step(m);
	assert(tos(m) == ref2);
	step(m);
	assert(!is_heap_freed(m, ref1));
	assert(!is_heap_freed(m, ref2));
	steps(m, 4);
	assert(!is_heap_freed(m, ref1));
	assert(is_heap_freed(m, ref2));
	steps(m, 3);
	assert(tos(m) == 18);
	step(m);
	assert(is_heap_freed(m, ref1));
	step(m);

	destroy_ijvm(m);
	fclose(output_file);
}

int main(void) {
	RUN_TEST(testGC1);
	RUN_TEST(testGC2);
	RUN_TEST(testGC3);
	RUN_TEST(testGC4);
	RUN_TEST(testGC5);
	return END_TEST();
}

#include "../include/ijvm.h"
#include <stdlib.h>

#include "testutil.h"

/* tests a precise garbage collector */
void testPreciseGC(void) {
	FILE *output_file = tmpfile();

	ijvm *m = init_ijvm("files/bonus/TestPreciseGC.ijvm", stdin, output_file);
	assert(m != NULL);

	step(m);
	assert(tos(m) == 32);
	step(m);
	assert(is_tos_reference(m));
	word ref1 = tos(m);
	steps(m, 2);
	assert(!is_tos_reference(m));
	step(m);
	assert(is_heap_freed(m, ref1));

	steps(m, 3);
	word ref2 = tos(m);
	step(m);
	assert(tos(m) == 42);
	step(m);
	assert(tos(m) == ref2);
	assert(is_tos_reference(m));
	step(m);
	assert(!is_heap_freed(m, ref2));
	steps(m, 2);
	assert(is_heap_freed(m, ref2));

	steps(m, 3);
	word ref3 = tos(m);
	steps(m, 3);
	assert(!is_heap_freed(m, ref3));
	steps(m, 2);
	assert(!is_heap_freed(m, ref3));
	steps(m, 2);
	assert(is_heap_freed(m, ref3));

	step(m);
	assert(tos(m) == 8);
	step(m);
	word ref4 = tos(m);
	steps(m, 4);
	assert(tos(m) == ref4);
	assert(!is_heap_freed(m, ref4));
	assert(!is_tos_reference(m));
	step(m);
	assert(is_heap_freed(m, ref4));

	steps(m, 3);
	word ref5 = tos(m);
	step(m);
	assert(tos(m) == 0);
	steps(m, 2);
	assert(!is_heap_freed(m, ref5));
	assert(tos(m) == ref5);
	step(m);
	assert(is_heap_freed(m, ref5));

	destroy_ijvm(m);
	fclose(output_file);
}

int main(void) {
	RUN_TEST(testPreciseGC);
	return END_TEST();
}

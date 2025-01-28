#include <stdlib.h>
#include "../include/ijvm.h"
#include "testutil.h"

/*
 *
 * This test comes with files/advanced/all_regular.ijvm, we recommend
 * reading it thorougly as it probably gives a very good insight into
 * what's wrong.
 *
 */

/* uncomment the next line to see all succesful tests */
// #define SHOW_ALL

#define stringify(x) #x
#define nputs(str) fprintf(stdout, str "\n")
#define nprintf(Fmt, ...) fprintf(stderr, "[+] " Fmt "\n", __VA_ARGS__)
#define eprintf(Fmt, ...) fprintf(stderr, "[!] " Fmt "\n", __VA_ARGS__)

/* function for debugging */
static inline void
_assert_equal(int line, const char *a_expr, word a, const char *b_expr, word b)
{
    if (a != b)
    {
        eprintf("line %d: Assert equal failed: %s (%d %#x) != %s (%d %#x)",
            line, a_expr, a, a, b_expr, b, b);
        exit(1);
    }
#ifdef SHOW_ALL
    else
        nprintf("line %d: Assert equal success: %s (%d %#x) == %s",
            line, a_expr, a, a, b_expr);
#endif
}

/* macro to print expressions of the statement */
#define assert_equal(a, b) _assert_equal(__LINE__, stringify(a), a, stringify(b), b)

/* Deal with windows annoyances */

#define TEST_FILE_PATH "files/advanced/all_regular.ijvm"

/*
 * Actual test function, this is the only stuff you'll need to read
 */
void test_advanced_1(void)
{
    FILE *input, *output;
    input  = fopen("tmp_input", "w+");
    output = fopen("tmp_output", "w+");

    ijvm* m = init_ijvm(TEST_FILE_PATH, input, output);
    assert(m != NULL);
    nputs("loaded machine");



    fputc('A', input);
    rewind(input);


    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 16);

    assert_equal(OP_DUP, get_instruction(m));
    step(m);
    assert_equal(tos(m), 16);

    assert_equal(OP_GOTO, get_instruction(m));
    step(m);

    assert_equal(OP_IADD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 32);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 33);

    assert_equal(OP_IAND, get_instruction(m));
    step(m);
    assert_equal(tos(m), 32);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 2);

    assert_equal(OP_IOR, get_instruction(m));
    step(m);
    assert_equal(tos(m), 3);

    assert_equal(OP_ISUB, get_instruction(m));
    step(m);
    assert_equal(tos(m), 29);

    assert_equal(OP_NOP, get_instruction(m));
    step(m);
    assert_equal(tos(m), 29);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 68);

    assert_equal(OP_IADD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 97);

    assert_equal(OP_OUT, get_instruction(m));
    step(m);
    assert_equal(fseek(output, 0, SEEK_SET), 0);
    assert_equal(fgetc(output), 'a');

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0);

    assert_equal(OP_IFEQ, get_instruction(m));
    step(m);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), -22);

    assert_equal(OP_IFLT, get_instruction(m));
    step(m);

    assert_equal(OP_LDC_W, get_instruction(m));
    step(m);
    assert_equal(tos(m), 65);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0x41);

    assert_equal(OP_IF_ICMPEQ, get_instruction(m));
    step(m);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_ISTORE, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_IINC, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 2);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_IN, get_instruction(m));
    step(m);
    assert_equal(tos(m), 'A');

    assert_equal(OP_IN, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0);

    assert_equal(OP_IFEQ, get_instruction(m));
    step(m);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 2);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 3);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 2);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 3);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 5);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction(m));
    step(m);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 10);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 0);

    assert_equal(OP_BIPUSH, get_instruction(m));
    step(m);
    assert_equal(tos(m), 1);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 5);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction(m));
    step(m);

    assert_equal(OP_ILOAD, get_instruction(m));
    step(m);
    assert_equal(tos(m), 5);

    assert_equal(OP_IRETURN, get_instruction(m));
    step(m);
    assert_equal(tos(m), 5);

    assert_equal(OP_POP, get_instruction(m));
    step(m);
    assert_equal(tos(m), 10);

    assert_equal(OP_IRETURN, get_instruction(m));
    step(m);
    assert_equal(tos(m), 10);

    assert_equal(OP_NOP, get_instruction(m));
    step(m);

    assert_equal(OP_IRETURN, get_instruction(m));
    step(m);
    assert_equal(tos(m), 10);

    assert_equal(OP_POP, get_instruction(m));
    step(m);

    assert_equal(OP_HALT, get_instruction(m));
    step(m);

    /* destroy the machine */
    destroy_ijvm(m);

    /* close temporary files */
    fclose(input);
    fclose(output);

    /* remove the temporary files */
    remove("tmp_input");
    remove("tmp_output");

}

int main(void)
{
  fprintf(stderr, "*** testadvanced2: ALL INSTRUCTIONS ...\n");
  RUN_TEST(test_advanced_1);
  return END_TEST();
}

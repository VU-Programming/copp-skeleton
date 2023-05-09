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
_assert_equal(int line, const char *a_expr, word_t a, const char *b_expr, word_t b)
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

    init_ijvm(TEST_FILE_PATH);
    nputs("loaded machine");

    input  = fopen("tmp_input", "w+");
    output = fopen("tmp_output", "w+");

    fputc('A', input);
    rewind(input);

    set_input(input);
    set_output(output);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 16);

    assert_equal(OP_DUP, get_instruction());
    step();
    assert_equal(tos(), 16);

    assert_equal(OP_GOTO, get_instruction());
    step();

    assert_equal(OP_IADD, get_instruction());
    step();
    assert_equal(tos(), 32);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 33);

    assert_equal(OP_IAND, get_instruction());
    step();
    assert_equal(tos(), 32);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 2);

    assert_equal(OP_IOR, get_instruction());
    step();
    assert_equal(tos(), 3);

    assert_equal(OP_ISUB, get_instruction());
    step();
    assert_equal(tos(), 29);

    assert_equal(OP_NOP, get_instruction());
    step();
    assert_equal(tos(), 29);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 68);

    assert_equal(OP_IADD, get_instruction());
    step();
    assert_equal(tos(), 97);

    assert_equal(OP_OUT, get_instruction());
    step();
    assert_equal(fseek(output, 0, SEEK_SET), 0);
    assert_equal(fgetc(output), 'a');

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 0);

    assert_equal(OP_IFEQ, get_instruction());
    step();

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), -22);

    assert_equal(OP_IFLT, get_instruction());
    step();

    assert_equal(OP_LDC_W, get_instruction());
    step();
    assert_equal(tos(), 65);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 0x41);

    assert_equal(OP_IF_ICMPEQ, get_instruction());
    step();

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_ISTORE, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_IINC, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 2);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_IN, get_instruction());
    step();
    assert_equal(tos(), 'A');

    assert_equal(OP_IN, get_instruction());
    step();
    assert_equal(tos(), 0);

    assert_equal(OP_IFEQ, get_instruction());
    step();

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 0);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 2);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 3);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 2);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 3);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 0);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 5);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction());
    step();

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 10);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 0);

    assert_equal(OP_BIPUSH, get_instruction());
    step();
    assert_equal(tos(), 1);

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 5);

    assert_equal(OP_INVOKEVIRTUAL, get_instruction());
    step();

    assert_equal(OP_ILOAD, get_instruction());
    step();
    assert_equal(tos(), 5);

    assert_equal(OP_IRETURN, get_instruction());
    step();
    assert_equal(tos(), 5);

    assert_equal(OP_POP, get_instruction());
    step();
    assert_equal(tos(), 10);

    assert_equal(OP_IRETURN, get_instruction());
    step();
    assert_equal(tos(), 10);

    assert_equal(OP_NOP, get_instruction());
    step();

    assert_equal(OP_IRETURN, get_instruction());
    step();
    assert_equal(tos(), 10);

    assert_equal(OP_POP, get_instruction());
    step();

    assert_equal(OP_HALT, get_instruction());
    step();

    /* destroy the machine */
    destroy_ijvm();

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

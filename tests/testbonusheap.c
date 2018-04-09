#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ijvm.h>
#include <assert.h>

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
#ifdef _WIN32
#define BFI_PATH    "files\\bonus\\bfi.ijvm"
#define HELLO_WORLD "files\\bonus\\brainfuck\\hello_world.bf"
#define DANKNESS    "files\\bonus\\brainfuck\\dank.bf"
#else
#define BFI_PATH    "files/bonus/bfi.ijvm"
#define HELLO_WORLD "files/bonus/brainfuck/hello_world.bf"
#define DANKNESS    "files/bonus/brainfuck/dank.bf"
#endif

void run_bfi(const char *bf_file, const char *expected)
{
    FILE *input, *output;
    char buffer[1024];
    int  bytes_read;

    init_ijvm(BFI_PATH);
    nputs("Loaded bfi");

    input  = fopen(bf_file, "r");
    output = fopen("tmp_output", "w+");
    assert(input);
    assert(output);

    set_input(input);
    set_output(output);
    nprintf("Running brainfuck file %s", bf_file);

    run();

    destroy_ijvm();

    /* re-open it for reading, since the ijvm closed it anyway */
    output = fopen("tmp_output", "r");

    if ((bytes_read = fread(buffer, 1, 1024, output)) < 0)
    {
        destroy_ijvm();
        eprintf("Couldn't read the output of the ijvm for program %s", bf_file);
        remove("tmp_output");
        return;
    }

    if (memcmp(buffer, expected, strlen(expected) - 1) != 0)
        eprintf("Incorrect output, got %s expected %s", buffer, expected);
    else
        eprintf("Successfully executed %s", bf_file);

    remove("tmp_output");
}

int main(int argc, char *argv[])
{
    run_bfi(HELLO_WORLD, "Hello World!");
    run_bfi(DANKNESS, "MoarTests");

    return 0;
}

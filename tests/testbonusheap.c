#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ijvm.h>
#include "testutil.h"

/* uncomment the next line to see all succesful tests */
// #define SHOW_ALL

#define stringify(x) #x
#define nputs(str) fprintf(stdout, str "\n")
#define nprintf(Fmt, ...) fprintf(stderr, "[+] " Fmt "\n", __VA_ARGS__)
#define eprintf(Fmt, ...) fprintf(stderr, "[!] " Fmt "\n", __VA_ARGS__)

#define BFI_PATH    "files/bonus/bfi2.ijvm"
#define HELLO_WORLD "files/bonus/brainfuck/hello_world.bf"
#define DANKNESS    "files/bonus/brainfuck/dank.bf"

void run_bfi(const char *bf_file, const char *expected)
{
    FILE *input, *output;
    char buffer[1024];
    int  bytes_read;

    assert(init_ijvm(BFI_PATH) != -1);
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
    fclose(input);
    fclose(output);

    /* re-open it for reading, since the ijvm closed it anyway */
    output = fopen("tmp_output", "r");

    if ((bytes_read = fread(buffer, 1, 1023, output)) < 0)
    {
        destroy_ijvm();
        eprintf("Couldn't read the output of the ijvm for program %s", bf_file);
        remove("tmp_output");
        exit(1);
    }
    /* add NIL byte at the end of the buffer */
    buffer[bytes_read] = 0;

    if (memcmp(buffer, expected, strlen(expected)+1) != 0)
    {
        eprintf("Incorrect output, got %s expected %s", buffer, expected);
        exit(1);
    }
    else
        eprintf("Successfully executed %s", bf_file);

    fclose(output);
    remove("tmp_output");
}

void test_bfi_1()
{
    run_bfi(HELLO_WORLD, "Hello World!\n");
}

void test_bfi_2()
{
    run_bfi(DANKNESS, "MoarTests");
}

int main(void)
{
    RUN_TEST(test_bfi_1);
    RUN_TEST(test_bfi_2);
    return END_TEST();
}

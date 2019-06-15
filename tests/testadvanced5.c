#include <stdio.h>
#include <string.h>
#include "ijvm.h"
#include "testutil.h"

void run_calc_inp(char *input, char *expected)
{
    int res = init_ijvm("files/advanced/SimpleCalc.ijvm");
    assert(res != -1);

    char buf[128];
    FILE *f = tmpfile();
    fprintf(f, "%s", input);
    rewind(f);
    set_input(f);

    FILE *out_file = tmpfile();
    set_output(out_file);

    // Run program
    run();

    rewind(out_file);
    memset(buf, '\0', 128);
    fread(buf, 1, 127, out_file);

    // Compare output
    assert(strncmp(buf, expected, strlen(expected)) == 0);

    destroy_ijvm();
    fclose(f);
    fclose(out_file);
}

void test_calc_1()
{
    run_calc_inp("0 0 + ? .", "0\n");
    run_calc_inp("0 9 + ? .", "9\n");
    run_calc_inp("9 0 + ? .", "9\n");
    run_calc_inp("9 9 - ? .", "0\n");
}

void test_calc_2()
{
    run_calc_inp("    5 4 -?.", "1\n");
    run_calc_inp("  8  8 8  - + ?.", "8\n");
}

void test_calc_3()
{
    run_calc_inp("1 1 + 1 1 + 1 1 + 1 1 + 1 1 + +-++?.", "2\n");
    run_calc_inp("9 8 -9 7-9 6-9 5-9 4-9 3-9 2-9 1-9 0- -+-+-+-+?.", "1\n");
}

void test_calc_4()
{
    run_calc_inp("2 2 2 2 2 2 2 2 2 2 2 2 2 ************ +?.", "8192\n");
}

int main()
{
    RUN_TEST(test_calc_1);
    RUN_TEST(test_calc_2);
    RUN_TEST(test_calc_3);
    RUN_TEST(test_calc_4);
    return END_TEST();
}

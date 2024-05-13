#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

/* testadvancedinterleave

This creates two IJVM interpreters and alternates steps between them.
This checks if you do not use global variables.

*/

void run_calc_interleave(char *input1, char *expected1, char* input2, char* expected2)
{
    
    char buf[128];
    FILE *inputf1 = tmpfile();
    fprintf(inputf1, "%s", input1);
    rewind(inputf1);

    FILE *out_file1 = tmpfile();
    ijvm* m1 = init_ijvm("files/advanced/SimpleCalc.ijvm",inputf1, out_file1);

    FILE *inputf2 = tmpfile();
    fprintf(inputf2, "%s", input2);
    rewind(inputf2);

    FILE *out_file2 = tmpfile();
    ijvm* m2 = init_ijvm("files/advanced/SimpleCalc.ijvm",inputf2, out_file2);
    assert(m2 != NULL);

    while(!finished(m1) || !finished(m2)) {
        if(!finished(m1)) step(m1);
        if(!finished(m2)) step(m2);
    }

    rewind(out_file1);
    memset(buf, '\0', 128);
    fread(buf, 1, 127, out_file1);

    // Compare output
    assert(strncmp(buf, expected1, strlen(expected1)) == 0);

    rewind(out_file2);
    memset(buf, '\0', 128);
    fread(buf, 1, 127, out_file2);

    // Compare output
    assert(strncmp(buf, expected2, strlen(expected2)) == 0);

    destroy_ijvm(m1);
    destroy_ijvm(m2);
    fclose(inputf1);
    fclose(out_file1);
    fclose(inputf2);
    fclose(out_file2);
}

void test_calc_1(void)
{
    run_calc_interleave("0 0 + ? .", "0\n","0 9 + ? .", "9\n");
    run_calc_interleave("9 0 + ? .", "9\n","9 9 - ? .", "0\n");
}

void test_calc_2(void)
{
    run_calc_interleave("    5 4 -?.", "1\n","  8  8 8  - + ?.", "8\n");
}

void test_calc_3(void)
{
    run_calc_interleave("1 1 + 1 1 + 1 1 + 1 1 + 1 1 + +-++?.", "2\n","9 8 -9 7-9 6-9 5-9 4-9 3-9 2-9 1-9 0- -+-+-+-+?.", "1\n");
}

void test_calc_4(void)
{
    run_calc_interleave("2 2 2 2 2 2 2 2 2 2 2 2 2 2 ************ +?.", "8194\n", "2 2 2 2 2 2 2 2 2 2 2 2 2 2 ************ +?.", "8194\n");
}

int main(void)
{
    fprintf(stderr, "*** testadvancedinterleave: No Globals ...\n");
    RUN_TEST(test_calc_1);
    RUN_TEST(test_calc_2);
    RUN_TEST(test_calc_3);
    RUN_TEST(test_calc_4);
    return END_TEST();
}

#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

/* testadvanced5: calc_facorial */

void run_calc_inp(char *input, char *expected)
{
    char buf[128];
    FILE *f = tmpfile();
    fprintf(f, "%s", input);
    rewind(f);

    FILE *out_file = tmpfile();
    ijvm* m = init_ijvm("files/advanced/SimpleCalc.ijvm",f, out_file);
    assert(m != NULL);


    // Run program
    run(m);

    rewind(out_file);
    memset(buf, '\0', 128);
    fread(buf, 1, 127, out_file);

    // Compare output
    assert(strncmp(buf, expected, strlen(expected)) == 0);

    destroy_ijvm(m);
    fclose(f);
    fclose(out_file);
}

void test_rec_1(void)
{
    run_calc_inp("2!?.", "2\n");
}

void test_rec_2(void)
{
    run_calc_inp("7!?.", "5040\n");
}

void test_rec_3(void)
{
    run_calc_inp("8!?.", "40320\n");
}

void test_rec_4(void)
{
    run_calc_inp("5!5+?.", "125\n");
}

int main(void)
{
    fprintf(stderr, "*** testadvanced5: CALC_FACTORIAL ...\n");
    RUN_TEST(test_rec_1);
    RUN_TEST(test_rec_2);
    RUN_TEST(test_rec_3);
    RUN_TEST(test_rec_4);
    return END_TEST();
}

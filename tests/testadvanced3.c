#include <stdio.h>
#include <string.h>
#include "../include/ijvm.h"
#include "testutil.h"

/* testadvanced3: tanenbaum */

void test_tanenbaum(void)
{
    FILE *output_file = tmpfile();
    char buf[128] = {0};

    memset(buf, '\0', 128);

    ijvm* m = init_ijvm("files/advanced/Tanenbaum.ijvm",stdin,output_file);
    assert(m != NULL);


    run(m);

    rewind(output_file);
    fread(buf, 1, 127, output_file);
    assert(strncmp(buf, "OK", 15) == 0);

    destroy_ijvm(m);
    fclose(output_file);
}

int main(void)
{
    fprintf(stderr, "*** testadvanced3: TANENBAUM ...\n");
    RUN_TEST(test_tanenbaum);
    return END_TEST();
}

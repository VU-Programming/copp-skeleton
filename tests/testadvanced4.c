#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "ijvm.h"


void test_tanenbaum()
{
    FILE *output_file;
    char buf[128];

    memset(buf, '\0', 128);

    int res = init_ijvm("files/advanced/Tanenbaum.ijvm");
    assert(res != -1);

    output_file = tmpfile();
    set_output(output_file);

    run();

    rewind(output_file);
    fread(buf, 1, 127, output_file);
    assert(strncmp(buf, "OK", 15) == 0);

    destroy_ijvm();

}

int main()
{
    test_tanenbaum();
    printf("## PASSED ALL TESTS FOR ADVANCED 4 ##\n");
    return 0;
}

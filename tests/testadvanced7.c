#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ijvm.h"
#include "testutil.h"

/*
 *  Hey there, everyone reading this test.
 *
 *  There's quite a lot going on in this test, since mandelbrot's are kind of difficult
 *  to draw... especially in a simulated environment without multiplication or division.
 *
 *  If this test doesn't work, it's probably worth it making sure you passed the other
 *  advanced tests first, and possibly getting your hands wet with goJASM for some custom
 *  tests. You can also check with the webijvm to figure out where your program starts showing
 *  different behaviour.
 *
 *  A further difficulty with this test is the time limit, if you don't know what you
 *  can do to improve performance, be sure to ask your TA or come to the practicals.
 *
 *  I'll try to answer any question about the specifics of the algorithms used on the
 *  discussion board if anyone has questions about that.
 *
 *  Good luck y'all :)
 *    - Arthur
 */


const char expected_output[] = \
    "                                                                                                    \n" \
    "                                                                                                    \n" \
    "                                                                                                    \n" \
    "                                                                         t`                         \n" \
    "                                                                         `':``'t@                   \n" \
    "                                                                        ``':L:``                    \n" \
    "                                                                     `t:':C@@8t'``                  \n" \
    "                                                                    `'f@@@@@@@@@@L`                 \n" \
    "                                                                   ``0@@@@@@@@@@@'`                 \n" \
    "                                                       ::`'8'```''''':tf@@@@@@@C:'''`'``      ``    \n" \
    "                                                       `fG@@G@::f@@@@@@@@@@@@@@@@@@@G@8:'`L''':'`   \n" \
    "                                                      ``'@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f@@@@8:@   \n" \
    "                                                    ``:::@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f`    \n" \
    "                                                  ``:8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L``   \n" \
    "                             't``     `t``      ```'@L@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:8`\n" \
    "                             `:tGt0:'':fG0:C'````''tC@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@G` \n" \
    "                            ```:f@@@0@@@@@@@@Gt:::t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@t'' \n" \
    "                          ```C:GC@@@@@@@@@@@@@@@@f8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:'  \n" \
    "                       'C''::t0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f'`  \n" \
    "         `          ```':L@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f`    \n" \
    "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L:'`     \n" \
    "         `          ```':L@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f`    \n" \
    "                       'C''::t0@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f'`  \n" \
    "                          ```C:GC@@@@@@@@@@@@@@@@f8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:'  \n" \
    "                            ```:f@@@0@@@@@@@@Gt:::t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@t'' \n" \
    "                             `:tGt0:'':fG0:C'````''tC@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@G` \n" \
    "                             't``     `t``      ```'@L@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:8`\n" \
    "                                                  ``:8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@L``   \n" \
    "                                                    ``:::@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f`    \n" \
    "                                                      ``'@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@f@@@@8:@   \n" \
    "                                                       `fG@@G@::f@@@@@@@@@@@@@@@@@@@G@8:'`L''':'`   \n" \
    "                                                       ::`'8'```''''':tf@@@@@@@C:'''`'``      ``    \n" \
    "                                                                   ``0@@@@@@@@@@@'`                 \n" \
    "                                                                    `'f@@@@@@@@@@L`                 \n" \
    "                                                                     `t:':C@@8t'``                  \n" \
    "                                                                        ``':L:``                    \n" \
    "                                                                         `':``'t@                   \n" \
    "                                                                         t`                         \n" \
    "                                                                                                    \n" \
    "                                                                                                    \n";

/*
 * Try executing 200000 steps to sample performance.
 *
 * Mandelbread has ~47 million steps, reference implementation takes 1.8 seconds
 * on a normal laptop, we test if the program is fast enough to complete this
 * test in reasonable time (< ~2min). To pass this test, your implementation has
 * to be fast enough.
 *
 * TL;DR if your implementation is too slow it will fail this test.
 */
static bool is_fast_enough(void)
{
    int i;
    clock_t start = clock();
    for(i = 0; !finished() && i < 200000; i++)
        step();

    clock_t end = clock();

    /* empirically determined, aka I tried some stuff,
       made sure to take outliers into account */
    const static double max_allowed = 0.70;

    double seconds = ((double) end - start) / CLOCKS_PER_SEC;
    return seconds < max_allowed;
}

static void run_mandelbread(void)
{
    int res = init_ijvm("files/advanced/mandelbread.ijvm");
    assert(res != -1);

    char *buf = calloc(sizeof(expected_output) + 1, sizeof(char));
    FILE *out_file = tmpfile();
    set_output(out_file);

    if (!is_fast_enough())
    {
        puts("Your IJVM implementation simply isn't fast enough to run");
        puts("mandelbread (testadvanced7)");

        destroy_ijvm();
        fclose(out_file);
        free(buf);
        assert(!"benchmark failed");
        return;
    }

    // Run program
    run();

    rewind(out_file);
    fread(buf, 1, sizeof(expected_output) + 1, out_file);
    printf("The glorious Mandelbread test output :D\n%s\n", buf);

    // Compare output
    assert(strncmp(buf, expected_output, sizeof(expected_output) + 1) == 0);
    destroy_ijvm();
    fclose(out_file);
    free(buf);
}

int main()
{
    RUN_TEST(run_mandelbread);
    return END_TEST();
}

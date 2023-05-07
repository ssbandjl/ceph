#include <stdio.h>
#include "hello-tp.h"

int main(int argc, char* argv[])
{
    int x;

    puts("Hello, World!\nPress Enter to continue...");

    /* The following getchar() call is only placed here for the purpose
     * of this demonstration, for pausing the application in order for
     * you to have time to list its events. It's not needed otherwise.
     */
    getchar();

    /* A tracepoint() call. Arguments, as defined in hello-tp.tp:
     *
     *     1st: provider name (always)
     *     2nd: tracepoint name (always)
     *     3rd: my_integer_arg (first user-defined argument)
     *     4th: my_string_arg (second user-defined argument)
     *
     * Notice the provider and tracepoint names are NOT strings;
     * they are in fact parts of variables created by macros in
     * hello-tp.h.
     */
    tracepoint(hello_world, my_first_tracepoint, 23, "hi there!");

    for (x = 0; x < argc; ++x) {
        tracepoint(hello_world, my_first_tracepoint, x, argv[x]);
    }

    puts("Quitting now!");

    tracepoint(hello_world, my_first_tracepoint, x * x, "x^2");

    return 0;
}


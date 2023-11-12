#include "error.h"

void error_usage (const char* x)
{
    fprintf(stderr, "dknow: usage: %s [-f <file>]\n", x);
    fprintf(stderr, "-f: File to be compiled.\n");
    exit(EXIT_SUCCESS);
}

void error_fatal (const char* why)
{
    fprintf(stderr, "dknow: fatal: %s :(\n", why);
    exit(EXIT_FAILURE);
}

void error_check (void* ptr)
{
    if (ptr) return;
    error_fatal("cannot allocate memory anymore");
}

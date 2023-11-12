#include "error.h"
#include <getopt.h>

static char* read_content (FILE*, size_t*);

int main (int argc, char** argv)
{
    if (argc == 1)
        error_usage(argv[0]);

    char* filename;
    char opt;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f': filename = optarg; break;
            default: error_usage(argv[0]); break;
        }
    }

    FILE* file = fopen(filename, "r");
    if (!file)
        error_fatal("file given does not work");

    size_t bytes;
    char* content = read_content(file, &bytes);

    printf("%s %ld\n", content, bytes);
    return 0;
}

static char* read_content (FILE* file, size_t* bytes)
{
    fseek(file, 0, SEEK_END);
    *bytes = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*) calloc(*bytes, 1);
    error_check(content);

    fread(content, *bytes, 1, file);
    content[--(*bytes)] = 0;

    fclose(file);
    return content;
}

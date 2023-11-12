#include "error.h"
#include "token.h"
#include <getopt.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

static char* read_content (FILE*, size_t*);
static void lexer_init (const char*, size_t);

static TokenType type_of_this (const char, const char);
static size_t go_deeper (const char*, size_t*, TokenType*);

static TokenType kind_of_this_word (const char*, size_t);

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

    lexer_init(content, bytes);
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

static void lexer_init (const char* src, size_t length)
{
    uint16_t numline = 1;

    for (size_t i = 0; i < length; i++) {
        const char a = src[i];

        if (a == 10) numline++;
        if (isspace(a)) continue;

        TokenType type = type_of_this(a, (i + 1 < length) ? src[1 + i] : 0);
        if (token_isnt_fixed_one(type)) {
            size_t prev = i, token_len;
            token_len = go_deeper(src, &i, &type);

            printf("token: %.*s <%d %d>\n", (int) token_len, src + prev, type, numline);
        }
        else {
            printf("fixed: %c <%d %d>\n", type, type, numline);
        }
    }
}

static TokenType type_of_this (const char a, const char b)
{
    switch (a) {
        case '#':
        case '(':
        case ')':
        case '{':
        case '}':
        case ';':
        case ',':
        case '+':
        case '/':
        case '*':
        case '%':
        case '$':
        case '"': return a;

        case '-': return isdigit(b) ? TypeLitNumber    : TypeSymSub;
        case '>': return (b == '=') ? TypeSymGreaterEq : TypeSymGreter;
        case '<': return (b == '=') ? TypeSymLessEq    : TypeSymLess;
        case '=': return (b == '=') ? TypeSym2Equals   : TypeSymEquals;
    }

    return isdigit(a) ? TypeLitNumber : TypeSymUnknown;
}

/* These function is called when the lexer cannot figure out
 * what type of token is the current one.
 * */
static bool GetStrings (const char c) { return c != '"'; }
static bool GetNumbers (const char c) { return isdigit(c); }
static bool GetWords   (const char c) { return isalnum(c) || c == '_'; }

static size_t go_deeper (const char* src, size_t* pos, TokenType* type)
{
    typedef bool (*gethis) (const char);
    gethis fx = GetWords;

    /**/ if (*type == TypeLitString) fx = GetStrings;
    else if (*type == TypeLitNumber) fx = GetNumbers;

    size_t len = 0;
    do {
        *pos += 1;
        len++;
    } while (fx(src[*pos]));

    /* Since strings are double quoted when
     * the last quote is reached such token
     * is not gonna be included since it is
     * what delimites the string so the lexer
     * will include it.
     *
     * For nonstring tokens the cursor position is
     * decreased since when the lexer get the next
     * character will skip the one which delimites
     * the current one: an_id(
     *                       ~ -> Would be skipped.
     * */
    if (*type == TypeLitString) len++;
    else *pos -= 1;

    if (*type == TypeSymUnknown)
        *type = kind_of_this_word(src, len);
    return len;
}

static TokenType kind_of_this_word (const char* token, size_t len)
{
    if (len == 3) {
        if (!strncmp(token, "ret", 3)) return TypeKwdReturn;
        if (!strncmp(token, "def", 3)) return TypeKwdDef;
    }

    return TypeLitId;
}

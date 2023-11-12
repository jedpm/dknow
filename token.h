#ifndef DKNOW_TOKEN_H
#define DKNOW_TOKEN_H

#define token_isnt_fixed_one(k) ((k == TypeLitNumber) || (k == TypeLitNumber) || (k == TypeSymUnknown))

typedef enum {
    TypeSymUnknown   = 0,
    TypeSymComment   = '#',
    TypeSymLeParen   = '(',
    TypeSymRiParen   = ')',
    TypeSymLeCurly   = '{',
    TypeSymRiCurly   = '}',
    TypeSymSemiCol   = ';',
    TypeSymComma     = ',',
    TypeSymSub       = '-',
    TypeSymAdd       = '+',
    TypeSymDiv       = '/',
    TypeSymMul       = '*',
    TypeSymMod       = '%',
    TypeSymGreter    = '>',
    TypeSymLess      = '<',
    TypeSymEquals    = '=',
    TypeSymMaths     = '?',
    TypeLitString    = '"',

    TypeSymGreaterEq = 256,
    TypeSymLessEq,
    TypeSym2Equals,

    TypeLitNumber,
    TypeLitId,
    TypeKwdDef,
    TypeKwdReturn,
} TokenType;

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

#endif

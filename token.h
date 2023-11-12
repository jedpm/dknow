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
    TypeLitString    = '"',

    TypeSymGreaterEq = 256,
    TypeSymLessEq,
    TypeSym2Equals,

    TypeLitNumber,
    TypeLitId,
    TypeKwdDef,
    TypeKwdReturn,
} TokenType;

#endif

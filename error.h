#ifndef DKNOW_ERROR_H
#define DKNOW_ERROR_H
#include <stdio.h>
#include <stdlib.h>

void error_usage (const char*);
void error_fatal (const char*);
void error_check (void*);

#endif

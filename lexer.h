
#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexerDef.h"

FILE *removeComments(FILE *testcaseFile, FILE *cleanFile);

char *extractLexeme(char *start, char *end);

void failState();

returnTK returnTKFactory(int t);

void initializeBuffers(char *filename);

void reloadBuffer(char *buf);

void incrementLexemeStart(int val);

void decForw(int val);

void incForw();

returnTK getNextTK();

void getStream(char *file_input);

void printTKs();

#endif
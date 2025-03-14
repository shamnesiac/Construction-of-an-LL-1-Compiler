/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7PS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
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

returnToken ReturnTokenFactory(int t);

void initializeBuffers(char *filename);

void reloadBuffer(char *buf);

void incrementLexemeStart(int val);

void decForw(int val);

void incForw();

returnToken getNextToken();

void getStream(char *file_input);

void printTokens();

#endif
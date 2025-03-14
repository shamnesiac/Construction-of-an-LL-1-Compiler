/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7PS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
#ifndef PARSERDEF_H
#define PARSERDEF_H

#include "lexer.h"
#include "lexerDef.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_TERMS 60
#define NUM_NONTERMS 53
#define NUM_ELEMENTS 114

enum Elements
{
    program,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    actualOrRedefined,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    fieldType,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    singleOrRecId,
    option_single_constructed,
    oneExpansion,
    moreExpansions,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    expPrime,
    term,
    termPrime,
    factor,
    highPrecedenceOperator,
    lowPrecedenceOperators,
    booleanExpression,
    var,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A,
    TKN_ERROR,
    TKN_ID,
    TKN_NUM,
    TKN_END,
    TKN_WHILE,
    TKN_UNION,
    TKN_ENDUNION,
    TKN_DEFINETYPE,
    TKN_AS,
    TKN_TYPE,
    TKN_MAIN,
    TKN_ASSIGNOP,
    TKN_COMMENT,
    TKN_FIELDID,
    TKN_GLOBAL,
    TKN_PARAMETER,
    TKN_MUL,
    TKN_DIV,
    TKN_CALL,
    TKN_RECORD,
    TKN_GT,
    TKN_GE,
    TKN_LIST,
    TKN_SQL,
    TKN_SQR,
    TKN_INPUT,
    TKN_ENDIF,
    TKN_READ,
    TKN_WRITE,
    TKN_RETURN,
    TKN_OUTPUT,
    TKN_ENDRECORD,
    TKN_ELSE,
    TKN_AND,
    TKN_OR,
    TKN_NOT,
    TKN_LT,
    TKN_LE,
    TKN_EQ,
    TKN_INT,
    TKN_REAL,
    TKN_COMMA,
    TKN_SEM,
    TKN_COLON,
    TKN_DOT,
    TKN_ENDWHILE,
    TKN_OP,
    TKN_CL,
    TKN_IF,
    TKN_THEN,
    TKN_PLUS,
    TKN_MINUS,
    TKN_RNUM,
    TKN_FUNID,
    TKN_RUID,
    TKN_WITH,
    TKN_PARAMETERS,
    TKN_NE,
    TKN_EPSILON,
    TKN_DOLLAR
};
typedef enum Elements Elements;

typedef struct NodeEle
{
    Elements item;
    struct NodeEle *next;
} node_Ele;
typedef node_Ele *NODE_ELE;

typedef struct LinkedListEle
{
    NODE_ELE head;
    int count;
} ll_ele;
typedef ll_ele *LL_ELE;

typedef struct NodeLL
{
    LL_ELE item;
    struct NodeLL *next;
} node_LL;
typedef node_LL *NODE_LL;

typedef struct LinkedListLL
{
    NODE_LL head;
    int count;
} ll_ll;
typedef ll_ll *LL_Set;

struct Stack
{
    LL_ELE list;
};
typedef struct Stack Stack;

typedef struct grammar
{
    LL_Set rules[NUM_NONTERMS];
} grammar;
typedef grammar *GRAMMAR;

typedef struct FirstAndFollow
{
    LL_ELE firstSet[NUM_ELEMENTS];
    LL_ELE followSet[NUM_NONTERMS];
} FirstAndFollow;
typedef struct FirstAndFollow *FIRSTANDFOLLOW;

struct ProdRule
{
    Elements LHS;
    Elements RHS[10];
    int count_rhs;
};
typedef struct ProdRule ProdRule;

struct TreeNode
{
    Elements x;     // NodeSymbol
    int lineNumber; // lineno
    char *value;    // ValueIfNumber
    char *lexeme;   // lexeme

    struct TreeNode *children[10];
    struct TreeNode *parent; // ParentNodeSymbol
    int count_children;      // isLeafNode
};
typedef struct TreeNode TreeNode;
typedef TreeNode *TREE_NODE;

#endif
/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7PS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "parserDef.h"

LL_Set createNewList_LL();
NODE_LL createNewNode_LL(LL_ELE data);
void insertNode_LLFirst(NODE_LL node, LL_Set list);
void insertNode_LLLast(NODE_LL node, LL_Set list);
void freeLL_Set(LL_Set list);

LL_ELE createNewList_Ele();
NODE_ELE createNewNode_Ele(Elements data);
void freeNode_Ele(NODE_ELE node);
void insertNode_EleFirst(NODE_ELE node, LL_ELE list);
void insertNode_EleLast(NODE_ELE node, LL_ELE list);
void removeNode_EleFirst(LL_ELE list);

Stack *createStack();
void push(Stack *stack, Elements element);
Elements top(Stack *stack);
void pop(Stack *stack);

void syncPopulateParseTable(FIRSTANDFOLLOW Fnf);
Elements stringToEnum(char *str);

void parseFileGrammar(char *filename);
int epsilonInFirst(LL_ELE first);
void computeFirst(FIRSTANDFOLLOW firstAndFollowSet);
void computeFollow(FIRSTANDFOLLOW firstAndFollowSet);

FIRSTANDFOLLOW computeFirstAndFollowSets();

ProdRule LLtoProd(Elements lhs, NODE_LL rule);
void initialiseParseTable();
void ParseTableEntry(FIRSTANDFOLLOW F, Elements lhs, ProdRule rule);
void createParseTable(FIRSTANDFOLLOW F);
TREE_NODE createTreeNode(Elements x, TREE_NODE parent, returnToken *k);
void createParseTree(Stack *st, TREE_NODE root, returnToken *flag);
TREE_NODE parseInputSourceCode();
void printParseTree(TREE_NODE root, char *outfile);

#endif
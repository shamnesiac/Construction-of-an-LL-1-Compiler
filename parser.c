/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7TS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
#include "parserDef.h"
#include <time.h>

extern GRAMMAR grammar_glob;
extern ProdRule ParseTable[NUM_NONTERMS][NUM_TERMS + 1];

// Providing functionality of :
// 1. Linked List of Elements,
// 2. Set of Linked Lists (Nested Linked Lists: used for production rules)
// 3. Stack (using Linked List)
LL_Set createNewList_LL()
{
    LL_Set list = malloc(sizeof(ll_ll));
    list->head = NULL;
    list->count = 0;
    return list;
}
NODE_LL createNewNode_LL(LL_ELE data)
{
    NODE_LL new_node = malloc(sizeof(node_LL));
    new_node->next = NULL;
    new_node->item = data;
    return new_node;
}

void insertNode_LLLast(NODE_LL node, LL_Set list)
{
    if (!node || !list)
        return;

    if (list->head == NULL)
        list->head = node;
    else
    {
        NODE_LL temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
    }
    node->next = NULL;
    list->count++;
}
LL_ELE createNewList_Ele()
{
    LL_ELE list = malloc(sizeof(ll_ele));
    list->head = NULL;
    list->count = 0;
    return list;
}
NODE_ELE createNewNode_Ele(Elements data)
{
    NODE_ELE new_node = malloc(sizeof(node_Ele));
    new_node->next = NULL;
    new_node->item = data;
    return new_node;
}
void insertNode_EleFirst(NODE_ELE node, LL_ELE list)
{
    node->next = list->head;
    list->head = node;
    list->count++;
}
void insertNode_EleLast(NODE_ELE node, LL_ELE list)
{
    if (!node || !list)
        return;

    if (list->head == NULL)
        list->head = node;
    else
    {
        NODE_ELE temp = list->head;
        while (temp->next)
            temp = temp->next;
        temp->next = node;
    }
    node->next = NULL;
    list->count++;
}
void freeNode_Ele(NODE_ELE node) { free(node); }
void removeNode_EleFirst(LL_ELE list)
{
    if (!list->head)
        return;

    NODE_ELE temp = list->head->next;
    NODE_ELE rem = list->head;
    list->head = temp;
    rem->next = NULL;
    list->count--;
    freeNode_Ele(rem);
}
Stack *createStack()
{
    Stack *st = (Stack *)malloc(sizeof(Stack));
    st->list = createNewList_Ele();
    return st;
}

void push(Stack *st, Elements element)
{

    NODE_ELE node = createNewNode_Ele(element);
    insertNode_EleFirst(node, st->list);
}

Elements top(Stack *st) { return ((st->list)->head)->item; }

void pop(Stack *st)
{
    if (!st || st->list->count <= 1 || !st->list)
    {
        return;
    }
    else
    {
        removeNode_EleFirst(st->list);
    }
}

// Populating Parse Table for terminals according to synchronizing array
void syncPopulateParseTable(FIRSTANDFOLLOW Fnf)
{
    // Terminals, at which a new line starts, from where we can resume parsing
    Elements syncArr[] = {TKN_ID, TKN_FUNID, TKN_RUID, TKN_WHILE, TKN_UNION, TKN_DEFINETYPE,
                           TKN_TYPE, TKN_MAIN, TKN_IF, TKN_READ, TKN_WRITE, TKN_RETURN,
                           TKN_CALL, TKN_RECORD, TKN_THEN, TKN_ELSE};
    for (int i = 0; i < NUM_NONTERMS; i++)
    {
        NODE_ELE ptr = Fnf->followSet[i]->head;
        // Configuring Parse Table for Terminals which belong to the respective Non-Terminal's Follow Set
        while (ptr != NULL)
        {
            if (ParseTable[i][ptr->item - NUM_NONTERMS].LHS == TKN_ERROR)
                ParseTable[i][ptr->item - NUM_NONTERMS].count_rhs = -1;
            ptr = ptr->next;
        }
        // Configuring Parse Table for Terminals at which new line begins
        for (int j = 0; j < 16; j++)
        {
            if (ParseTable[i][syncArr[j] - NUM_NONTERMS].LHS == TKN_ERROR)
                ParseTable[i][syncArr[j] - NUM_NONTERMS].count_rhs = -1;
        }
    }
}

// Converting Elements enum to according string
char *TKToString[] = {"program",
                         "mainFunction",
                         "otherFunctions",
                         "function",
                         "input_par",
                         "output_par",
                         "parameter_list",
                         "dataType",
                         "primitiveDatatype",
                         "constructedDatatype",
                         "remaining_list",
                         "stmts",
                         "typeDefinitions",
                         "actualOrRedefined",
                         "typeDefinition",
                         "fieldDefinitions",
                         "fieldDefinition",
                         "fieldType",
                         "moreFields",
                         "declarations",
                         "declaration",
                         "global_or_not",
                         "otherStmts",
                         "stmt",
                         "assignmentStmt",
                         "singleOrRecId",
                         "option_single_constructed",
                         "oneExpansion",
                         "moreExpansions",
                         "funCallStmt",
                         "outputParameters",
                         "inputParameters",
                         "iterativeStmt",
                         "conditionalStmt",
                         "elsePart",
                         "ioStmt",
                         "arithmeticExpression",
                         "expPrime",
                         "term",
                         "termPrime",
                         "factor",
                         "highPrecedenceOperator",
                         "lowPrecedenceOperators",
                         "booleanExpression",
                         "var",
                         "logicalOp",
                         "relationalOp",
                         "returnStmt",
                         "optionalReturn",
                         "idList",
                         "more_ids",
                         "definetypestmt",
                         "A",
                         "TK_ERROR",
                         "TK_ID",
                         "TK_NUM",
                         "TK_END",
                         "TK_WHILE",
                         "TK_UNION",
                         "TK_ENDUNION",
                         "TK_DEFINETYPE",
                         "TK_AS",
                         "TK_TYPE",
                         "TK_MAIN",
                         "TK_ASSIGNOP",
                         "TK_COMMENT",
                         "TK_FIELDID",
                         "TK_GLOBAL",
                         "TK_PARAMETER",
                         "TK_MUL",
                         "TK_DIV",
                         "TK_CALL",
                         "TK_RECORD",
                         "TK_GT",
                         "TK_GE",
                         "TK_LIST",
                         "TK_SQL",
                         "TK_SQR",
                         "TK_INPUT",
                         "TK_ENDIF",
                         "TK_READ",
                         "TK_WRITE",
                         "TK_RETURN",
                         "TK_OUTPUT",
                         "TK_ENDRECORD",
                         "TK_ELSE",
                         "TK_AND",
                         "TK_OR",
                         "TK_NOT",
                         "TK_LT",
                         "TK_LE",
                         "TK_EQ",
                         "TK_INT",
                         "TK_REAL",
                         "TK_COMMA",
                         "TK_SEM",
                         "TK_COLON",
                         "TK_DOT",
                         "TK_ENDWHILE",
                         "TK_OP",
                         "TK_CL",
                         "TK_IF",
                         "TK_THEN",
                         "TK_PLUS",
                         "TK_MINUS",
                         "TK_RNUM",
                         "TK_FUNID",
                         "TK_RUID",
                         "TK_WITH",
                         "TK_PARAMETERS",
                         "TK_NE",
                         "TK_EPSILON",
                         "TK_DOLLAR"};

// Converting Elements enum to according string
Elements stringToTK(char *str)
{
    if (strcmp(str, "TK_ERROR") == 0)
    {
        return TKN_ERROR;
    }
    else if (strcmp(str, "TK_ASSIGNOP") == 0)
    {
        return TKN_ASSIGNOP;
    }
    else if (strcmp(str, "TK_COMMENT") == 0)
    {
        return TKN_COMMENT;
    }
    else if (strcmp(str, "TK_FIELDID") == 0)
    {
        return TKN_FIELDID;
    }
    else if (strcmp(str, "TK_ID") == 0)
    {
        return TKN_ID;
    }
    else if (strcmp(str, "TK_NUM") == 0)
    {
        return TKN_NUM;
    }
    else if (strcmp(str, "TK_RNUM") == 0)
    {
        return TKN_RNUM;
    }
    else if (strcmp(str, "TK_FUNID") == 0)
    {
        return TKN_FUNID;
    }
    else if (strcmp(str, "TK_RUID") == 0)
    {
        return TKN_RUID;
    }
    else if (strcmp(str, "TK_WITH") == 0)
    {
        return TKN_WITH;
    }
    else if (strcmp(str, "TK_PARAMETERS") == 0)
    {
        return TKN_PARAMETERS;
    }
    else if (strcmp(str, "TK_END") == 0)
    {
        return TKN_END;
    }
    else if (strcmp(str, "TK_WHILE") == 0)
    {
        return TKN_WHILE;
    }
    else if (strcmp(str, "TK_UNION") == 0)
    {
        return TKN_UNION;
    }
    else if (strcmp(str, "TK_ENDUNION") == 0)
    {
        return TKN_ENDUNION;
    }
    else if (strcmp(str, "TK_DEFINETYPE") == 0)
    {
        return TKN_DEFINETYPE;
    }
    else if (strcmp(str, "TK_AS") == 0)
    {
        return TKN_AS;
    }
    else if (strcmp(str, "TK_TYPE") == 0)
    {
        return TKN_TYPE;
    }
    else if (strcmp(str, "TK_MAIN") == 0)
    {
        return TKN_MAIN;
    }
    else if (strcmp(str, "TK_GLOBAL") == 0)
    {
        return TKN_GLOBAL;
    }
    else if (strcmp(str, "TK_PARAMETER") == 0)
    {
        return TKN_PARAMETER;
    }
    else if (strcmp(str, "TK_LIST") == 0)
    {
        return TKN_LIST;
    }
    else if (strcmp(str, "TK_SQL") == 0)
    {
        return TKN_SQL;
    }
    else if (strcmp(str, "TK_SQR") == 0)
    {
        return TKN_SQR;
    }
    else if (strcmp(str, "TK_INPUT") == 0)
    {
        return TKN_INPUT;
    }
    else if (strcmp(str, "TK_OUTPUT") == 0)
    {
        return TKN_OUTPUT;
    }
    else if (strcmp(str, "TK_INT") == 0)
    {
        return TKN_INT;
    }
    else if (strcmp(str, "TK_REAL") == 0)
    {
        return TKN_REAL;
    }
    else if (strcmp(str, "TK_COMMA") == 0)
    {
        return TKN_COMMA;
    }
    else if (strcmp(str, "TK_SEM") == 0)
    {
        return TKN_SEM;
    }
    else if (strcmp(str, "TK_COLON") == 0)
    {
        return TKN_COLON;
    }
    else if (strcmp(str, "TK_DOT") == 0)
    {
        return TKN_DOT;
    }
    else if (strcmp(str, "TK_ENDWHILE") == 0)
    {
        return TKN_ENDWHILE;
    }
    else if (strcmp(str, "TK_OP") == 0)
    {
        return TKN_OP;
    }
    else if (strcmp(str, "TK_CL") == 0)
    {
        return TKN_CL;
    }
    else if (strcmp(str, "TK_IF") == 0)
    {
        return TKN_IF;
    }
    else if (strcmp(str, "TK_THEN") == 0)
    {
        return TKN_THEN;
    }
    else if (strcmp(str, "TK_ENDIF") == 0)
    {
        return TKN_ENDIF;
    }
    else if (strcmp(str, "TK_READ") == 0)
    {
        return TKN_READ;
    }
    else if (strcmp(str, "TK_WRITE") == 0)
    {
        return TKN_WRITE;
    }
    else if (strcmp(str, "TK_RETURN") == 0)
    {
        return TKN_RETURN;
    }
    else if (strcmp(str, "TK_PLUS") == 0)
    {
        return TKN_PLUS;
    }
    else if (strcmp(str, "TK_MINUS") == 0)
    {
        return TKN_MINUS;
    }
    else if (strcmp(str, "TK_MUL") == 0)
    {
        return TKN_MUL;
    }
    else if (strcmp(str, "TK_DIV") == 0)
    {
        return TKN_DIV;
    }
    else if (strcmp(str, "TK_CALL") == 0)
    {
        return TKN_CALL;
    }
    else if (strcmp(str, "TK_RECORD") == 0)
    {
        return TKN_RECORD;
    }
    else if (strcmp(str, "TK_ENDRECORD") == 0)
    {
        return TKN_ENDRECORD;
    }
    else if (strcmp(str, "TK_ELSE") == 0)
    {
        return TKN_ELSE;
    }
    else if (strcmp(str, "TK_AND") == 0)
    {
        return TKN_AND;
    }
    else if (strcmp(str, "TK_OR") == 0)
    {
        return TKN_OR;
    }
    else if (strcmp(str, "TK_NOT") == 0)
    {
        return TKN_NOT;
    }
    else if (strcmp(str, "TK_LT") == 0)
    {
        return TKN_LT;
    }
    else if (strcmp(str, "TK_LE") == 0)
    {
        return TKN_LE;
    }
    else if (strcmp(str, "TK_EQ") == 0)
    {
        return TKN_EQ;
    }
    else if (strcmp(str, "TK_GT") == 0)
    {
        return TKN_GT;
    }
    else if (strcmp(str, "TK_GE") == 0)
    {
        return TKN_GE;
    }
    else if (strcmp(str, "TK_NE") == 0)
    {
        return TKN_NE;
    }
    else if (strcmp(str, "TK_EPSILON") == 0)
    {
        return TKN_EPSILON;
    }
    else if (strcmp(str, "TK_DOLLAR") == 0)
    {
        return TKN_DOLLAR;
    }
    else if (strcmp(str, "program") == 0)
    {
        return program;
    }
    else if (strcmp(str, "mainFunction") == 0)
    {
        return mainFunction;
    }
    else if (strcmp(str, "otherFunctions") == 0)
    {
        return otherFunctions;
    }
    else if (strcmp(str, "function") == 0)
    {
        return function;
    }
    else if (strcmp(str, "input_par") == 0)
    {
        return input_par;
    }
    else if (strcmp(str, "output_par") == 0)
    {
        return output_par;
    }
    else if (strcmp(str, "parameter_list") == 0)
    {
        return parameter_list;
    }
    else if (strcmp(str, "dataType") == 0)
    {
        return dataType;
    }
    else if (strcmp(str, "primitiveDatatype") == 0)
    {
        return primitiveDatatype;
    }
    else if (strcmp(str, "constructedDatatype") == 0)
    {
        return constructedDatatype;
    }
    else if (strcmp(str, "remaining_list") == 0)
    {
        return remaining_list;
    }
    else if (strcmp(str, "stmts") == 0)
    {
        return stmts;
    }
    else if (strcmp(str, "typeDefinitions") == 0)
    {
        return typeDefinitions;
    }
    else if (strcmp(str, "actualOrRedefined") == 0)
    {
        return actualOrRedefined;
    }
    else if (strcmp(str, "typeDefinition") == 0)
    {
        return typeDefinition;
    }
    else if (strcmp(str, "fieldDefinitions") == 0)
    {
        return fieldDefinitions;
    }
    else if (strcmp(str, "fieldDefinition") == 0)
    {
        return fieldDefinition;
    }
    else if (strcmp(str, "fieldType") == 0)
    {
        return fieldType;
    }
    else if (strcmp(str, "moreFields") == 0)
    {
        return moreFields;
    }
    else if (strcmp(str, "declarations") == 0)
    {
        return declarations;
    }
    else if (strcmp(str, "declaration") == 0)
    {
        return declaration;
    }
    else if (strcmp(str, "global_or_not") == 0)
    {
        return global_or_not;
    }
    else if (strcmp(str, "otherStmts") == 0)
    {
        return otherStmts;
    }
    else if (strcmp(str, "stmt") == 0)
    {
        return stmt;
    }
    else if (strcmp(str, "stmt") == 0)
    {
        return stmt;
    }
    else if (strcmp(str, "assignmentStmt") == 0)
    {
        return assignmentStmt;
    }
    else if (strcmp(str, "singleOrRecId") == 0)
    {
        return singleOrRecId;
    }
    else if (strcmp(str, "option_single_constructed") == 0)
    {
        return option_single_constructed;
    }
    else if (strcmp(str, "oneExpansion") == 0)
    {
        return oneExpansion;
    }
    else if (strcmp(str, "moreExpansions") == 0)
    {
        return moreExpansions;
    }
    else if (strcmp(str, "funCallStmt") == 0)
    {
        return funCallStmt;
    }
    else if (strcmp(str, "outputParameters") == 0)
    {
        return outputParameters;
    }
    else if (strcmp(str, "inputParameters") == 0)
    {
        return inputParameters;
    }
    else if (strcmp(str, "iterativeStmt") == 0)
    {
        return iterativeStmt;
    }
    else if (strcmp(str, "conditionalStmt") == 0)
    {
        return conditionalStmt;
    }
    else if (strcmp(str, "elsePart") == 0)
    {
        return elsePart;
    }
    else if (strcmp(str, "ioStmt") == 0)
    {
        return ioStmt;
    }
    else if (strcmp(str, "arithmeticExpression") == 0)
    {
        return arithmeticExpression;
    }
    else if (strcmp(str, "expPrime") == 0)
    {
        return expPrime;
    }
    else if (strcmp(str, "term") == 0)
    {
        return term;
    }
    else if (strcmp(str, "termPrime") == 0)
    {
        return termPrime;
    }
    else if (strcmp(str, "factor") == 0)
    {
        return factor;
    }
    else if (strcmp(str, "highPrecedenceOperator") == 0)
    {
        return highPrecedenceOperator;
    }
    else if (strcmp(str, "lowPrecedenceOperators") == 0)
    {
        return lowPrecedenceOperators;
    }
    else if (strcmp(str, "booleanExpression") == 0)
    {
        return booleanExpression;
    }
    else if (strcmp(str, "var") == 0)
    {
        return var;
    }
    else if (strcmp(str, "logicalOp") == 0)
    {
        return logicalOp;
    }
    else if (strcmp(str, "relationalOp") == 0)
    {
        return relationalOp;
    }
    else if (strcmp(str, "returnStmt") == 0)
    {
        return returnStmt;
    }
    else if (strcmp(str, "optionalReturn") == 0)
    {
        return optionalReturn;
    }
    else if (strcmp(str, "idList") == 0)
    {
        return idList;
    }
    else if (strcmp(str, "more_ids") == 0)
    {
        return more_ids;
    }
    else if (strcmp(str, "definetypestmt") == 0)
    {
        return definetypestmt;
    }
    else if (strcmp(str, "A") == 0)
    {
        return A;
    }
    return -1;
}

// Parsing grammar.txt to convert into Grammar, which is an array of Set of Linked Lists
void parseFileGrammar(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Error in opening file\n");
        return;
    }
    for (int i = 0; i < NUM_NONTERMS; i++)
    {
        grammar_glob->rules[i] = createNewList_LL();
    }
    char buff[1024];
    while (fgets(buff, 1024, fp) != NULL)
    {
        char delim1[] = " ";
        char delim2[] = "\n";

        char *fullLine = strtok(buff, delim2);
        char *firstptr = strtok(fullLine, delim1);
        int LHS_NonTerm = stringToTK(firstptr);
        firstptr = strtok(NULL, delim1);
        firstptr = strtok(NULL, delim1);
        LL_ELE curr = createNewList_Ele();
        while (firstptr)
        {
            if (firstptr[0] == ';')
            {
                insertNode_LLLast(createNewNode_LL(curr),
                                  grammar_glob->rules[LHS_NonTerm]);
                curr = createNewList_Ele();
                firstptr = strtok(NULL, delim1);
                continue;
            }
            NODE_ELE one = createNewNode_Ele(stringToTK(firstptr));
            insertNode_EleLast(one, curr);
            firstptr = strtok(NULL, delim1);
        }
        insertNode_LLLast(createNewNode_LL(curr),
                          grammar_glob->rules[LHS_NonTerm]);
    }
    fclose(fp);
    return;
}

// Checking epsilon in a Linked List of terminals
int epsilonInFirst(LL_ELE first)
{
    NODE_ELE ptr = first->head;
    while (ptr != NULL)
    {
        if (ptr->item == TKN_EPSILON)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

// Computing First Sets of all Elements based on Grammar
void computeFirst(FIRSTANDFOLLOW firstAndFollowSet)
{
    /*
    1. If X is a terminal, then FIRST(X) = {X}.
    2. If X is a nonterminal and X -> Y1 Y2 ... Yk is a production for some k >=
    1, then place a in FIRST(X) if for some i, a is in FIRST(Yi), and eps is in
    all of       eps. If eps is in FIRST(Y ) FIRST(Y1 ); : : : ; FIRST(Yi,1 );
    that is, Y1 ... Yi,1 )
    j
    for all j = 1; 2; : : : ; k, then add eps to FIRST(X ). For example,
    everything in FIRST(Y1 ) is surely in FIRST(X ). If Y1 does not derive eps,
    then we add eps, then we add FIRST(Y ), and nothing more to FIRST(X ), but
    if Y1 )
    2
    so on.
    3. If X -> eps is a production, then add eps to FIRST(X).
    */

    int change = 1;
    Elements lhs = TKN_ERROR;
    for (; lhs < NUM_ELEMENTS; lhs++)
    {
        insertNode_EleLast(createNewNode_Ele(lhs),
                           firstAndFollowSet->firstSet[lhs]);
    }
    while (change)
    {
        change = 0;
        lhs = program;
        for (; lhs < NUM_NONTERMS; lhs++)
        {
            NODE_ELE firstLhsHead = firstAndFollowSet->firstSet[lhs]->head;
            NODE_LL currRHS = grammar_glob->rules[lhs]->head;

            if (currRHS->item->head->item == TKN_EPSILON &&
                !epsilonInFirst(firstAndFollowSet->firstSet[lhs]))
            {
                insertNode_EleLast(createNewNode_Ele(TKN_EPSILON),
                                   firstAndFollowSet->firstSet[lhs]);
                currRHS = currRHS->next;
                continue;
            }
            while (currRHS != NULL)
            {
                NODE_ELE currTerm = currRHS->item->head;
                while (currTerm != NULL)
                {
                    NODE_ELE firstTerm =
                        firstAndFollowSet->firstSet[currTerm->item]->head;
                    while (firstTerm != NULL)
                    {
                        if (firstTerm->item == TKN_EPSILON)
                        {
                            firstTerm = firstTerm->next;
                            continue;
                        }
                        NODE_ELE tempLhs = firstLhsHead;
                        int visited = 0;
                        while (tempLhs != NULL)
                        {
                            if (tempLhs->item == firstTerm->item)
                                visited = 1;
                            tempLhs = tempLhs->next;
                        }
                        if (!visited)
                        {
                            insertNode_EleLast(
                                createNewNode_Ele(firstTerm->item),
                                firstAndFollowSet->firstSet[lhs]);
                            change = 1;
                        }
                        firstTerm = firstTerm->next;
                    }
                    if (currTerm->next == NULL &&
                        epsilonInFirst(
                            firstAndFollowSet->firstSet[currTerm->item]) &&
                        !epsilonInFirst(firstAndFollowSet->firstSet[lhs]))
                        insertNode_EleLast(createNewNode_Ele(TKN_EPSILON),
                                           firstAndFollowSet->firstSet[lhs]);
                    if (!epsilonInFirst(
                            firstAndFollowSet->firstSet[currTerm->item]))
                        break;
                    currTerm = currTerm->next;
                }

                currRHS = currRHS->next;
            }
        }
    }
}

// Computing Follow Sets of all Elements based on Grammar and First sets
void computeFollow(FIRSTANDFOLLOW firstAndFollowSet)
{
    /*
    1. Place $ in FOLLOW(S), where S is the start symbol, and $ is the input
    right endmarker.
    2. If there is a production A->aBb , then everything in FIRST(b) except eps
    is in FOLLOW(B).
    3. If there is a production A->aB , or a production A->aBb , where FIRST(b)
    contains eps, then everything in FOLLOW(A) is in FOLLOW(B).
    */
    insertNode_EleLast(createNewNode_Ele(stringToTK("TK_DOLLAR")),
                       firstAndFollowSet->followSet[0]);
    int change = 1;
    while (change)
    {
        change = 0;
        int lhs = 0;
        for (; lhs < NUM_NONTERMS; lhs++)
        {
            NODE_LL currRHS = grammar_glob->rules[lhs]->head;
            while (currRHS != NULL)
            {
                NODE_ELE currTerm = currRHS->item->head;
                NODE_ELE nextTerm = currTerm;
                while (currTerm != NULL)
                {
                    if (currTerm->item >= NUM_NONTERMS)
                    {
                        currTerm = currTerm->next;
                        nextTerm = currTerm;
                        continue;
                    }

                    nextTerm = nextTerm->next;

                    if (nextTerm == NULL)
                    {

                        NODE_ELE lhsPtr =
                            firstAndFollowSet->followSet[lhs]->head;
                        while (lhsPtr != NULL)
                        {
                            Elements term = lhsPtr->item;
                            NODE_ELE bPtr =
                                firstAndFollowSet->followSet[currTerm->item]
                                    ->head;
                            int visited = 0;
                            while (bPtr != NULL)
                            {
                                if (bPtr->item == term)
                                    visited = 1;
                                bPtr = bPtr->next;
                            }
                            if (!visited)
                            {
                                insertNode_EleLast(
                                    createNewNode_Ele(term),
                                    firstAndFollowSet
                                        ->followSet[currTerm->item]);
                                change = 1;
                            }
                            lhsPtr = lhsPtr->next;
                        }
                    }
                    else
                    {
                        NODE_ELE betaPtr =
                            firstAndFollowSet->firstSet[nextTerm->item]->head;
                        while (betaPtr != NULL)
                        {
                            Elements term = betaPtr->item;
                            if (term == TKN_EPSILON)
                            {
                                betaPtr = betaPtr->next;
                                continue;
                            }
                            NODE_ELE bPtr =
                                firstAndFollowSet->followSet[currTerm->item]
                                    ->head;
                            int visited = 0;
                            while (bPtr != NULL)
                            {
                                if (bPtr->item == term)
                                    visited = 1;
                                bPtr = bPtr->next;
                            }
                            if (!visited)
                            {
                                insertNode_EleLast(
                                    createNewNode_Ele(term),
                                    firstAndFollowSet
                                        ->followSet[currTerm->item]);
                                change = 1;
                            }
                            betaPtr = betaPtr->next;
                        }
                        if (epsilonInFirst(
                                firstAndFollowSet->firstSet[nextTerm->item]))
                            continue;
                        if (epsilonInFirst(
                                firstAndFollowSet->firstSet[nextTerm->item]) &&
                            (nextTerm->next == NULL))
                        {
                            NODE_ELE lhsPtr =
                                firstAndFollowSet->followSet[lhs]->head;
                            while (lhsPtr != NULL)
                            {
                                Elements term = lhsPtr->item;
                                NODE_ELE bPtr =
                                    firstAndFollowSet->followSet[currTerm->item]
                                        ->head;
                                int visited = 0;
                                while (bPtr != NULL)
                                {
                                    if (bPtr->item == term)
                                        visited = 1;
                                    bPtr = bPtr->next;
                                }
                                if (!visited)
                                {
                                    insertNode_EleLast(
                                        createNewNode_Ele(term),
                                        firstAndFollowSet
                                            ->followSet[currTerm->item]);
                                    change = 1;
                                }
                                lhsPtr = lhsPtr->next;
                            }
                        }
                    }
                    currTerm = currTerm->next;
                    nextTerm = currTerm;
                }
                currRHS = currRHS->next;
            }
        }
    }
}

// Driver function for calling Computing First and Follow sets
FIRSTANDFOLLOW computeFirstAndFollowSets()
{
    FIRSTANDFOLLOW firstAndFollowSet =
        (FIRSTANDFOLLOW)malloc(sizeof(FirstAndFollow));
    for (int i = 0; i < NUM_NONTERMS; i++)
    {
        firstAndFollowSet->firstSet[i] = createNewList_Ele();
        firstAndFollowSet->followSet[i] = createNewList_Ele();
    }
    for (int i = NUM_NONTERMS; i < NUM_ELEMENTS; i++)
        firstAndFollowSet->firstSet[i] = createNewList_Ele();
    computeFirst(firstAndFollowSet);
    computeFollow(firstAndFollowSet);
    return firstAndFollowSet;
}

ProdRule LLtoProd(Elements lhs, NODE_LL rule)
{
    ProdRule ans;
    ans.LHS = lhs;
    for (int i = 0; i < 10; i++)
        ans.RHS[i] = TKN_ERROR;
    NODE_ELE ptr = rule->item->head;
    int cnt = 0;
    while (ptr)
    {
        ans.RHS[cnt++] = ptr->item;
        ptr = ptr->next;
    }
    ans.count_rhs = cnt;
    return ans;
}

void initialiseParseTable()
{
    for (int i = 0; i < NUM_NONTERMS; i++)
    {
        for (int j = 0; j < NUM_TERMS + 1; j++)
        {
            ParseTable[i][j].LHS = TKN_ERROR;
            for (int k = 0; k < 10; k++)
            {
                ParseTable[i][j].RHS[k] = TKN_ERROR;
            }
            ParseTable[i][j].count_rhs = 0;
        }
    }
}

// Populating Parse Table helper function
void ParseTableEntry(FIRSTANDFOLLOW F, Elements lhs, ProdRule rule)
{
    LL_ELE setToAdd = createNewList_Ele();
    bool flag = false;
    for (int i = 0; i < rule.count_rhs; i++)
    {
        if (!epsilonInFirst(F->firstSet[rule.RHS[i]]))
        {
            NODE_ELE temp1 = F->firstSet[rule.RHS[i]]->head;
            while (temp1)
            {
                NODE_ELE insert1 = createNewNode_Ele(temp1->item);
                insertNode_EleLast(insert1, setToAdd);
                temp1 = temp1->next;
            }
            flag = true;
            break;
        }
        if (rule.RHS[i] != TKN_EPSILON)
        {
            NODE_ELE temp2 = F->firstSet[rule.RHS[i]]->head;
            while (temp2)
            {
                if (temp2->item == TKN_EPSILON)
                {
                    temp2 = temp2->next;
                    continue;
                }
                NODE_ELE insert2 = createNewNode_Ele(temp2->item);
                insertNode_EleLast(insert2, setToAdd);
                temp2 = temp2->next;
            }
        }
    }
    if (!flag)
    {
        NODE_ELE temp3 = F->followSet[lhs]->head;
        while (temp3)
        {
            if (temp3->item == TKN_EPSILON)
            {
                temp3 = temp3->next;
                continue;
            }
            NODE_ELE insert3 = createNewNode_Ele(temp3->item);
            insertNode_EleLast(insert3, setToAdd);
            temp3 = temp3->next;
        }
    }
    NODE_ELE temp4 = setToAdd->head;
    while (temp4)
    {
        if (temp4->item != TKN_EPSILON)
            ParseTable[lhs][temp4->item - NUM_NONTERMS] = rule;
        temp4 = temp4->next;
    }
}

void createParseTable(FIRSTANDFOLLOW F)
{
    for (int i = 0; i < NUM_NONTERMS; i++)
    {
        LL_Set rulesForNonTerm = grammar_glob->rules[i];
        NODE_LL currRule = rulesForNonTerm->head;
        while (currRule)
        {
            ProdRule temp = LLtoProd(i, currRule);
            ParseTableEntry(F, i, temp);
            currRule = currRule->next;
        }
    }
}

// TreeNode creation and inserting nodes
TREE_NODE createTreeNode(Elements x, TREE_NODE parent, returnTK *k)
{
    TREE_NODE y = malloc(sizeof(TreeNode));
    y->value = malloc(25 * sizeof(char));
    y->value = "----";
    if ((x == TKN_NUM || x == TKN_RNUM) && (k->t == TK_NUM || k->t == TK_RNUM))
    {
        y->value = NULL;
        free(y->value);
        y->value = malloc(25 * sizeof(char));
        strcpy(y->value, k->lexeme);
    }

    if (x >= NUM_NONTERMS)
    {
        y->lexeme = k->lexeme;
        y->lineNumber = k->line;
    }
    else
    {
        y->lexeme = "----";
        y->lineNumber = -1;
    }
    y->x = x;
    y->parent = parent;
    for (int i = 0; i < 10; i++)
        y->children[i] = NULL;
    return y;
}

// Parsing helper function based on stack and input stream, and populating Parse Tree
// Global variable, for if error has occurred
int errorred = 0;
// Global variable, for not printing multiple redundant errors
int redundantErrors = 0;
void createParseTree(Stack *st, TREE_NODE root, returnTK *k)
{
    Elements a = top(st);
    while (k->flag == -3)
    {
        *k = getNextTK();
        // root -> lexeme = k -> lexeme;
    }
    // printf("TK: %d  lexeme: %s  flag: %d root -> x: %s stack top: %s\n", k ->t, k -> lexeme, k -> flag, TKToString[root -> x], TKToString[a]);
    while (k->t == TK_COMMENT)
    {
        *k = getNextTK();
    }
    // printf("TK: %d  lexeme: %s  flag: %d root -> x: %s stack top: %s\n", k ->t, k -> lexeme, k -> flag, TKToString[root -> x], TKToString[a]);
    while (k->flag == -3)
    {
        *k = getNextTK();
    }
    // printf("line: %d TK: %d  lexeme: %s  flag: %d root -> x: %s stack top: %s\n", k->line, k->t, k->lexeme, k->flag, TKToString[root->x], TKToString[a]);
    root->lexeme = k->lexeme;
    if (k->line >= 40 && k->line <= 46)
    {
        // printf("line: %d TK: %d  lexeme: %s  flag: %d root -> x: %s stack top: %s\n", k->line, k->t, k->lexeme, k->flag, TKToString[root->x], TKToString[a]);
        // printf("line = %d root lexeme = %s k lexeme = %s\n", k->line, root->lexeme, k->lexeme);
    }
    if (k->flag == -1 && k->lexeme != NULL)
        errorred = 1;
    if (a == TKN_DOLLAR)
    {
        if (k->flag == -2)
        {
            return;
        }
        else
        {
            if (redundantErrors == 0)
            {
                printf("\033[0;31m");
                printf("Line %d Error :", k->line);
                printf("\033[0;33m");
                printf("Completed Parse Tree generation, but extra TKs were found in input file\n");
                printf("\033[0m");
            }
            redundantErrors = 1;
            errorred = 1;
            return;
        }
    }
    else
    {
        if (k->flag == -1)
        {
            // Start of File
            if (k->lexeme == NULL)
            {
                *k = getNextTK();
                createParseTree(st, root, k);
                return;
            }
            // When, Unknown pattern/Symbol is coming in input
            *k = getNextTK();
            createParseTree(st, root, k);
            return;
        }
        if (k->flag == -2)
        {
            // EOF reached
            if (redundantErrors == 0)
            {
                printf("\033[0;31m");
                printf("File Ended before Parse Tree was formed completely\n");
                printf("\033[0m");
            }
            redundantErrors = 1;
            errorred = 1;
            return;
        }
    }
    if (root->x == TKN_EPSILON)
        return;

    if (a < NUM_NONTERMS)
    {
        ProdRule rule = ParseTable[a][k->t];

        if (rule.LHS != TKN_ERROR)
        {
            // Valid Parse Table entry reached, inputting in Parse tree accordingly
            redundantErrors = 0;
            pop(st);

            root->count_children = rule.count_rhs;
            for (int i = rule.count_rhs - 1; i >= 0; i--)
            {
                if (rule.RHS[i] != TKN_EPSILON)
                {
                    push(st, rule.RHS[i]);
                }
            }
            for (int i = 0; i < rule.count_rhs; i++)
            {
                root->children[i] = createTreeNode(rule.RHS[i], root, k);
                createParseTree(st, root->children[i], k);
            }
            if (top(st) == TKN_DOLLAR && k->flag != -2)
            {
                errorred = 1;
                if (redundantErrors == 0)
                {
                    printf("\033[0;31m");
                    printf("Line %d Error :", k->line);
                    printf("\033[0;33m");
                    printf(" File Ended before Parse Tree was formed completely\n");
                    printf("\033[0m");
                }
                redundantErrors = 1;
            }
            return;
        }
        else
        {
            // Error, syntactically incorrect as no production rule found
            // Input terminal doesnt match top of Stack non terminal
            errorred = 1;
            if (redundantErrors == 0)
            {
                printf("\033[0;31m");
                printf("Line %d Error :", k->line);
                printf("\033[0;33m");
                printf(" Invalid TK %s encountered with value %s stack top %s\n",
                       TKToString[k->t + NUM_NONTERMS], k->lexeme, TKToString[a]);
                printf("\033[0m");
            }

            redundantErrors = 1;
            if (rule.count_rhs == 0)
            {
                *k = getNextTK();
                createParseTree(st, root, k);
                return;
            }
            if (rule.count_rhs == -1)
            {
                pop(st);
                createParseTree(st, root, k);
                return;
            }
        }
    }
    else
    {
        if (k->t == a - NUM_NONTERMS)
        {
            // Top of stack Terminal matches Input terminal
            pop(st);
            *k = getNextTK();
            return;
        }
        else
        {
            errorred = 1;
            // Error, Incorrect terminal found, not matching top of stack terminal

            if (redundantErrors == 0)
            {
                printf("\033[0;31m");
                printf("Line %d Error :", k->line);
                printf("\033[0;33m");
                printf(" The TK %s for lexeme %s does not match with the expected TK %s\n",
                       TKToString[k->t + NUM_NONTERMS], k->lexeme, TKToString[a]);
                printf("\033[0m");
            }
            redundantErrors = 1;
            pop(st);

            createParseTree(st, root, k);
        }
    }

    return;
}

TREE_NODE parseInputSourceCode()
{

    Stack *st = createStack();
    push(st, TKN_DOLLAR);

    push(st, program);
    errorred = 0;
    redundantErrors = 0;
    returnTK *r = malloc(sizeof(returnTK));
    r->t = TK_ERROR;
    r->lexeme = NULL;
    r->flag = -1;
    TREE_NODE root = createTreeNode(program, NULL, r);
    createParseTree(st, root, r);
    if (errorred == 0)
    {

        printf("\033[0;92m");
        printf("Code is ");
        printf("\033[0;95m");
        printf("SYNTACTICALLY");
        printf("\033[0;92m");
        printf(" correct\n");
        printf("\033[0m");
    }
    return root;
}

void inOrderTraversal(FILE *fp, TREE_NODE root)
{
    char *lexeme = root->lexeme;
    int lineNumber = root->lineNumber;
    char *TKName = TKToString[root->x];

    char *nodeSymbol = "----";
    char *isLeafNode = "Yes";

    char *parent = "ROOT";

    if (root->parent)
        parent = TKToString[root->parent->x];

    if (root->count_children)
    {
        lexeme = "----";
        inOrderTraversal(fp, root->children[0]);
        TKName = "----";
        nodeSymbol = TKToString[root->x];
        isLeafNode = "No";
    }

    // lexeme CurrentNode lineno TKName valueIfNumber parentNodeSymbol isLeafNode(yes/no) NodeSymbol
    if (lineNumber != -1)
        fprintf(fp, "%-25s%-10d%-20s%-20s%-30s%-10s%-20s\n", lexeme, lineNumber,
                TKName, root->value, parent, isLeafNode, nodeSymbol);
    else
        fprintf(fp, "%-25s----      %-20s%-20s%-30s%-10s%-20s\n", lexeme,
                TKName, root->value, parent, isLeafNode, nodeSymbol);

    for (int i = 1; i < root->count_children; i++)
        inOrderTraversal(fp, root->children[i]);

    return;
}

void printParseTree(TREE_NODE root, char *outfile)
{
    FILE *fp = fopen(outfile, "w+");
    fprintf(fp, "Lexeme                   Line No.  TK Name          Number Value        Parent Node Symbol             is Leaf   Node Symbol\n");
    inOrderTraversal(fp, root);
    fclose(fp);
    // if (errorred == 1)
    // {
    //     fp = fopen(outfile, "w+");
    //     fprintf(fp, "Error in parsing encountered, so parse tree couldn't be generated\n");
    //     fclose(fp);
    // }
    return;
}
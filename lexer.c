/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7PS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
#include "lexerDef.h"

FILE *fpct;
int state;
int lineNumber;
char *buffer1;
char *buffer2;
char *lexemeStart;
char *forward;
Token tk;

#define EMP (char *)malloc(0) // check this ***SUPER IMPORTANT***
#define MAX_STRING_SIZE 100   // Maximum length of key and value
#define TABLE_SIZE 53         // Prime number for better distribution

// Structure for a key-value pair (node in a linked list)
typedef struct Node
{
    char key[50];
    int value;
    struct Node *next;
} Node;

// Hash table (array of linked list heads)
Node *hashTable[TABLE_SIZE];

// Optimized djb2 hash function
unsigned int hashFunction(char *key)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % TABLE_SIZE;
}

// Insert key-value pair
void insert(char *key, int value)
{
    unsigned int index = hashFunction(key);
    Node *current = hashTable[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value; // Update existing key
            return;
        }
        current = current->next;
    }

    // Insert new node
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Get value by key
int get(char *key)
{
    unsigned int index = hashFunction(key);
    Node *current = hashTable[index];

    while (current)
    {
        if (strcmp(current->key, key) == 0)
            return current->value;
        current = current->next;
    }
    return -1; // Not found
}

// Delete a key from the map
void deleteKey(char *key)
{
    unsigned int index = hashFunction(key);
    Node *current = hashTable[index];
    Node *prev = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                hashTable[index] = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Print all key-value pairs
void printMap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = hashTable[i];
        while (current)
        {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}

// Free all allocated memory
void freeMap()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node *current = hashTable[i];
        while (current)
        {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

// Inserts keywords into trie
void populateMap()
{

    insert("real", TK_REAL);
    insert("int", TK_INT);
    insert("read", TK_READ);
    insert("with", TK_WITH);
    insert("parameters", TK_PARAMETERS);
    insert("end", TK_END);
    insert("while", TK_WHILE);
    insert("global", TK_GLOBAL);
    insert("parameter", TK_PARAMETER);
    insert("list", TK_LIST);
    insert("input", TK_INPUT);
    insert("record", TK_RECORD);
    insert("endrecord", TK_ENDRECORD);
    insert("union", TK_UNION);
    insert("endunion", TK_ENDUNION);
    insert("definetype", TK_DEFINETYPE);
    insert("output", TK_OUTPUT);
    insert("write", TK_WRITE);
    insert("endwhile", TK_ENDWHILE);
    insert("if", TK_IF);
    insert("then", TK_THEN);
    insert("endif", TK_ENDIF);
    insert("return", TK_RETURN);
    insert("call", TK_CALL);
    insert("as", TK_AS);
    insert("type", TK_TYPE);
    insert("else", TK_ELSE);
    insert("_main", TK_MAIN);
}

// Checks whether word is in trie
enum Token lookupMap(char *word)
{
    return get(word);
}

//===================   CHANGE THIS      ==============================
// Array of tokens
char *tokensArr[] = {
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
};

//===================   CHANGE THIS      ==============================
// Removes comments from file provided
// check return TK_comment waala portion
FILE *removeComments(FILE *testcaseFile, FILE *cleanFile)
{

    // open the file in which we supposed to write

    if (testcaseFile == NULL || cleanFile == NULL)
    {
        // handle error in opening of any file
        printf("Error reading file");
        exit(1);
    }

    char c; // read character by character input in this variable
    bool start = 0;
    // if start==0, no comment is being read
    // if start==1, a comment is being read

    while ((c = fgetc(testcaseFile)) != EOF)
    {
        if (c == '%')
        {
            // comment start
            start = 1;
        }
        if (start == 0)
        {
            // write only when no comment is being read
            fputc(c, cleanFile);
        }
        if (start == 1 && c == '\n')
        {
            // if comment is in progress and we encounter endline, end the
            // comment
            start = 0;
            lineNumber++;
            fputc('\n', cleanFile);
        }
    }
    return cleanFile;
}

// Returns the substring between the pointers `start` and `end`
char *extractLexeme(char *start, char *end)
{
    if (start == end)
    {
        return strdup(""); // Using strdup instead of manually allocating ""
    }

    // Validate buffer range conditions
    if ((start <= (buffer1 + BUFFER_SIZE + 1) && end <= (buffer1 + BUFFER_SIZE + 1)) ||
        ((start > (buffer1 + BUFFER_SIZE + 1) && start <= (buffer2 + BUFFER_SIZE + 1)) &&
         (end > (buffer1 + BUFFER_SIZE + 1) && end <= (buffer2 + BUFFER_SIZE + 1))))
    {
        if (end < start)
        {
            printf("\033[0;31mWarning: Token exceeded buffer size, truncating lexeme.\033[0m\n");
            start = end;
            return strdup("");
        }
        size_t length = end - start;
        char *result = (char *)malloc(length);
        strncpy(result, start, length - 1);
        result[length - 1] = '\0';
        return result;
    }
    else
    {
        char *midpoint = NULL;
        char *part1 = NULL;
        char *part2 = NULL;

        if (start <= (buffer1 + BUFFER_SIZE) && end <= (buffer2 + BUFFER_SIZE))
        {
            midpoint = buffer1 + BUFFER_SIZE;
            size_t len1 = midpoint - start;
            size_t len2 = end - buffer2;

            part1 = (char *)malloc(len1);
            strncpy(part1, start, len1 - 1);
            part1[len1 - 1] = '\0';

            part2 = (char *)malloc(len2);
            strncpy(part2, buffer2, len2 - 1);
            part2[len2 - 1] = '\0';
        }
        else
        {
            midpoint = buffer2 + BUFFER_SIZE;
            size_t len1 = midpoint - start;
            size_t len2 = end - buffer1;

            part1 = (char *)malloc(len1);
            strncpy(part1, start, len1 - 1);
            part1[len1 - 1] = '\0';

            part2 = (char *)malloc(len2);
            strncpy(part2, buffer1, len2 - 1);
            part2[len2 - 1] = '\0';
        }

        char *finalResult = (char *)malloc(strlen(part1) + strlen(part2) + 1);
        strcpy(finalResult, part1);
        strcat(finalResult, part2);

        free(part1);
        free(part2);

        return finalResult;
    }
}

//======== done till here =========
// Deals with lexer errors (unknown symbol and unknown pattern)
// when we get an error state we are calling this function
void failState()
{
    if (strlen(extractLexeme(lexemeStart, forward)) == 0)
    {
        printf("\033[0;31m");
        printf("Line %d Error : ", lineNumber);
        printf("\033[0;33m");
        printf("Unknown symbol <");
        printf("%c", *lexemeStart);
        printf(">\n");
        printf("\033[0m");
    }
    else if (strlen(extractLexeme(lexemeStart, forward)) == 1)
    {
        printf("\033[0;31m");
        printf("Line %d Error : ", lineNumber);
        printf("\033[0;33m");
        printf("Unknown symbol <");
        printf("%s", extractLexeme(lexemeStart, forward));
        printf(">\n");
        printf("\033[0m");
    }
    else
    {
        printf("\033[0;31m");
        printf("Line %d Error : ", lineNumber);
        printf("\033[0;33m");
        printf("Unknown pattern <");
        printf("%s", extractLexeme(lexemeStart, forward));
        printf(">\n");
        printf("\033[0m");
    }
}

// Returns struct encapsulating info for terminal node of parse tree

returnToken ReturnTokenFactory(int t)
{
    returnToken r;

    if (t == -3)
    {
        /////finalise this case
        r.flag = t;
        r.lexeme = EMP;
        r.line = lineNumber;
        return r;
    }
    if (t == -2)
    {
        r.flag = t;
        r.lexeme = extractLexeme(lexemeStart, forward);
        r.line = lineNumber;
        return r;
    }
    if (t < 0)
    {
        r.flag = t;
        r.t = TK_ERROR;
        r.lexeme = extractLexeme(lexemeStart, forward);
        r.line = lineNumber;
        return r;
    }
    r.flag = 1;
    r.t = t;
    r.line = lineNumber;
    char *lex = extractLexeme(lexemeStart, forward);
    if (tk == TK_COMMENT)
    {
        r.lexeme = "%";
    }
    else if (tk != TK_ID || strlen(lex) <= 20) // if not TK_ID then add check for 30, else 2 to 20
    {
        r.lexeme = lex;
    }
    else
    {
        printf("\033[0;31m");
        printf("Line %d Error :", lineNumber);
        printf("\033[0;33m");
        printf(" Variable Identifier is longer than the prescribed length of 20 characters.\n");
        printf("\033[0m");
        r.lexeme = lex;
        r.flag = -1;
    }
    return r;
}

// Reads file into buffers
void initializeBuffers(char *fileName)
{
    buffer1 = (char *)calloc(BUFFER_SIZE + 2, sizeof(char));
    buffer2 = (char *)calloc(BUFFER_SIZE + 2, sizeof(char));

    fpct = fopen(fileName, "r");

    fseek(fpct, 0, SEEK_SET);
    int readlen = 0;
    if (fpct && !feof(fpct))
    {
        readlen = fread(buffer1, sizeof(char), BUFFER_SIZE, fpct);
    }
    if (feof(fpct))
    {
        buffer1[readlen++] = ' ';
    }
    buffer1[readlen++] = '\0';
}

// Reloads buffer with file contents
void reloadBuffer(char *buf)
{
    int readlen = 0;
    fseek(fpct, -1, SEEK_CUR);
    if (fpct && !feof(fpct))
        readlen = fread(buf, sizeof(char), BUFFER_SIZE, fpct);
    if (feof(fpct))
        buf[readlen++] = ' ';
    buf[readlen++] = '\0';
}

// Increments lexemeStart condition-wise
void incrementlexemeStart(int val)
{
    for (int i = 0; i < val; i++)
    {
        if (*(lexemeStart + 1) != '\0')
            lexemeStart++;
        else if ((lexemeStart - buffer1) < BUFFER_SIZE + 2)
            lexemeStart = buffer2;
        else
            lexemeStart = buffer1;
    }
}

// Decrements forward condition-wise
void decForw(int val)
{
    if (forward == buffer1)
    {
        forward = buffer2 + BUFFER_SIZE - val;
    }
    else if (forward == buffer2)
    {
        forward = buffer1 + BUFFER_SIZE - val;
    }
    else
    {
        forward -= val;
    }
}

// Increments forward condition-wise
void incForw()
{
    if ((forward) == (buffer1 + BUFFER_SIZE + 1) ||
        (forward) == (buffer1 + BUFFER_SIZE + 2))
    {
        reloadBuffer(buffer2);
        forward = buffer2;
    }
    else if ((forward) == (buffer2 + BUFFER_SIZE + 1) ||
             (forward) == (buffer2 + BUFFER_SIZE + 2))
    {
        reloadBuffer(buffer1);
        forward = buffer1;
    }
    else
    {
        forward++;
    }
}

/*
    This function returns the next token.
    The file pointer for the file to be read has been kept global and hence is not
    required to be passed.
*/
returnToken getNextToken()
{
    returnToken r;
    bool reloaded = false;
    while (1)
    {
        if (reloaded)
        {
            forward++;
            reloaded = false;
        }
        char c = *forward;
        switch (*(forward++))
        {
        case '\0':
            if ((forward) == (buffer1 + BUFFER_SIZE + 1) ||
                (forward) == (buffer1 + BUFFER_SIZE + 2))
            {
                // reload buffer2
                reloadBuffer(buffer2);
                // set forward to buffer2
                forward = buffer2;
                reloaded = true;
            }
            else if ((forward) == (buffer2 + BUFFER_SIZE + 1) ||
                     (forward) == (buffer2 + BUFFER_SIZE + 2))
            {
                // reload buffer1
                reloadBuffer(buffer1);
                // set forward to buffer1
                forward = buffer1;
                reloaded = true;
            }
            else
            {
                // terminate lexical analysis
                r = ReturnTokenFactory(-2);

                return r;
            }
            break;
        default:
            switch (state)
            {
            case 0:
                switch (c)
                {
                case '+':
                    state = 1;
                    break;
                case '*':
                    state = 2;
                    break;
                case '-':
                    state = 3;
                    break;
                case '/':
                    state = 4;
                    break;
                case '~':
                    state = 5;
                    break;
                case '(':
                    state = 6;
                    break;
                case ')':
                    state = 7;
                    break;
                case '[':
                    state = 8;
                    break;
                case ']':
                    state = 9;
                    break;
                case ';':
                    state = 10;
                    break;
                case ':':
                    state = 11;
                    break;
                case ',':
                    state = 12;
                    break;
                case '.':
                    state = 13;
                    break;
                case '&':
                    state = 14;
                    break;
                case '@':
                    state = 17;
                    break;
                case '#':
                    state = 20;
                    break;
                case '_':
                    state = 23;
                    break;
                case '<':
                    state = 28;
                    break;
                case '>':
                    state = 35;
                    break;
                case '\n':
                    state = 63;
                    lineNumber++;
                    break;
                case '\t':
                    state = 63;
                    break;
                case ' ':
                    state = 63;
                    break;
                case '\r':
                    state = 63;
                    break;
                case '=':
                    state = 38;
                    break;
                case '!':
                    state = 40;
                    break;
                case '%':
                    state = 65;
                    break;
                default:
                    if (c >= '0' && c <= '9')
                    {
                        state = 52;
                    }
                    else if (c >= 'b' && c <= 'd')
                    {
                        state = 44;
                    }
                    else if (c >= 'a' && c <= 'z')
                    {
                        state = 42;
                    }
                    else
                    {
                        // This should give the failure state
                        // Since none of the recognizable characters are taken
                        failState();
                        r = ReturnTokenFactory(-1);
                        lexemeStart = forward;
                        state = 0;
                        return r;
                    }
                    break;
                }
                break;
                // case 0 ends here
            case 1:
                // final state
                state = 0;
                tk = TK_PLUS;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 1 ends here
            case 2:
                // final state
                state = 0;
                tk = TK_MUL;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 2 ends here
            case 3:
                // final state
                state = 0;
                tk = TK_MINUS;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 3 ends here
            case 4:
                // final state
                state = 0;
                tk = TK_DIV;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 4 ends here
            case 5:
                // final state
                state = 0;
                tk = TK_NOT;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 5 ends here
            case 6:
                // final state
                state = 0;
                tk = TK_OP;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 6 ends here
            case 7:
                // final state
                state = 0;
                tk = TK_CL;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 7 ends here
            case 8:
                // final state
                state = 0;
                tk = TK_SQL;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 8 ends here
            case 9:
                // final state
                state = 0;
                tk = TK_SQR;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 9 ends here
            case 10:
                // final state
                state = 0;
                tk = TK_SEM;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 11:
                // final state
                state = 0;
                tk = TK_COLON;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 11 ends here
            case 12:
                // final state
                state = 0;
                tk = TK_COMMA;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 13:
                // final state
                state = 0;
                tk = TK_DOT;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 13 ends here
            case 14:
                if (c == '&')
                {
                    state = 15;
                }
                else
                {
                    // other condition
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(1);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 14 ends here
            case 15:
                if (c == '&')
                {
                    state = 16;
                }
                else
                {
                    // other condition
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(2);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 15 ends here
            case 16:
                // final state
                tk = TK_AND;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 16 ends here
            case 17:
                if (c == '@')
                {
                    state = 18;
                }
                else
                {
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(1);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 17 ends here
            case 18:
                if (c == '@')
                {
                    state = 19;
                }
                else
                {
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(1);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 18 ends here
            case 19:
                // final state
                tk = TK_OR;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 19 ends here
            case 20:
                // final state
                if (c >= 'a' && c <= 'z')
                {
                    state = 21;
                }
                else
                {
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(1);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 20 ends here
            case 21:
                if (c >= 'a' && c <= 'z')
                {
                    state = 21;
                }
                else
                {
                    decForw(1);
                    state = 22;
                }
                break;
                // case 21 ends here
            case 22:
                // final state
                tk = TK_RUID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 22 ends here;
            case 23:
                if (c >= 'a' && c <= 'z')
                    state = 24;
                else if (c >= 'A' && c <= 'Z')
                    state = 24;
                else
                {
                    // other condition
                    failState();
                    r = ReturnTokenFactory(-1);
                    state = 0;
                    incrementlexemeStart(1);
                    forward = lexemeStart;
                    return r;
                }
                break;
                // case 23 ends here
            case 24:
                if (c >= 'a' && c <= 'z')
                    state = 24;
                else if (c >= 'A' && c <= 'Z')
                    state = 24;
                else if (c >= '0' && c <= '9')
                    state = 25;
                else
                {
                    state = 26;
                    decForw(1);
                }
                // final state
                break;
                // case 24 ends here
            case 25:
                if (c >= '0' && c <= '9')
                    state = 25;
                else
                {
                    state = 27;
                    decForw(1);
                }
                // final state
                break;
                // case 25 ends here
            case 26:
                // other condition
                //================= CONFIRM FOR _MAIN  ===============
                tk = TK_FUNID;
                char *m = extractLexeme(lexemeStart, forward);
                char *m2 = (char *)malloc(sizeof(char) * 5);
                m2 = "_main";
                // printf("%s %s %d\n",m, m2, strcmp(m,m2) );
                if (strcmp(m, m2) == 0)
                {
                    tk = TK_MAIN;
                }
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
                // case 26 ends here
            case 27:
                // other condition
                tk = TK_FUNID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                // case 27 ends here
            case 28:
                // final state
                if (c == '=')
                {
                    state = 29;
                }
                else if (c == '-')
                {
                    state = 31;
                }
                else
                {
                    state = 30;
                    decForw(1);
                }
                break;
                // case 28 ends here
            case 29:
                // final state
                tk = TK_LE;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                // final state
                break;
                // case 29 ends here
            case 30:
                tk = TK_LT;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
            case 31:
                if (c == '-')
                {
                    state = 32;
                }
                else
                {
                    state = 34;
                    decForw(1);
                }
                break;
            case 32:
                if (c == '-')
                {
                    state = 33;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                break;
            case 33:
                // final state
                tk = TK_ASSIGNOP;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 34:
                tk = TK_LT;
                decForw(1);
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
            case 35:
                // final state
                if (c == '=')
                {
                    state = 37;
                }
                else
                {
                    state = 36;
                }
                break;
            case 36:
                // other condition
                state = 0;
                tk = TK_GT;
                r = ReturnTokenFactory(tk);
                decForw(1);
                lexemeStart = forward;
                return r;
            case 37:
                // final state
                tk = TK_GE;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 38:
                if (c == '=')
                {
                    state = 39;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
            case 39:
                // final state
                tk = TK_EQ;
                r = ReturnTokenFactory(tk);
                state = 0;
                lexemeStart = forward;
                return r;
                break;
            case 40:
                if (c == '=')
                {
                    state = 41;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                // case 40 ends here
            case 41:
                // final
                tk = TK_NE;
                r = ReturnTokenFactory(tk);
                state = 0;
                lexemeStart = forward;
                return r;
                break;
                // case 41 ends here
            case 42:
                if (c >= 'a' && c <= 'z')
                {
                    state = 42;
                }
                else
                {
                    state = 43;
                    decForw(1);
                }
                break;
            case 43:
                state = 0;
                char *mn = extractLexeme(lexemeStart, forward);
                tk = get(mn);
                if (tk == -1)
                {
                    tk = TK_FIELDID;
                    r = ReturnTokenFactory(tk);
                    decForw(1);
                    lexemeStart = forward;
                    return r;
                }
                else
                {
                    r = ReturnTokenFactory(tk);
                    decForw(1);
                    lexemeStart = forward;
                    return r;
                }
                break;
            case 44:
                if (c >= 'a' && c <= 'z')
                    state = 42;
                else if (c >= '2' && c <= '7')
                    state = 45;
                else
                {
                    state = 49;
                }
                // final state
                break;
            case 45:
                if (c >= '2' && c <= '7')
                    state = 47;
                else if (c >= 'b' && c <= 'd')
                {
                    state = 46;
                }
                else
                {
                    state = 50;
                    decForw(1);
                }
                // final state
                break;
            case 46:
                if (c >= '2' && c <= '7')
                    state = 47;
                else if (c >= 'b' && c <= 'd')
                {
                    state = 46;
                }
                else
                {
                    decForw(1);
                    state = 51;
                }
                // final state
                break;
            case 47:
                if (c >= '2' && c <= '7')
                    state = 47;
                else
                {
                    state = 48;
                    decForw(1);
                }
                break;
            case 48:
                // other condition
                tk = TK_ID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 49:
                tk = TK_FIELDID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 50:
                // other condition
                tk = TK_ID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 51:
                // other condition
                tk = TK_ID;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 52:
                if (c >= '0' && c <= '9')
                {
                    state = 52;
                }
                else if (c == '.')
                {
                    state = 53;
                }
                else
                {
                    state = 60;
                    decForw(1);
                }
                break;
            case 53:
                if (c >= '0' && c <= '9')
                {
                    state = 54;
                }
                else
                {
                    state = 61;
                    decForw(1);
                }
                break;
            case 54:
                if (c >= '0' && c <= '9')
                {
                    state = 55;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                break;
            case 55:
                if (c == 'E')
                {
                    state = 56;
                }
                else
                {
                    decForw(1);
                    state = 62;
                }
                break;
            case 56:
                if (c == '+' || c == '-')
                {
                    state = 57;
                }
                else if (c >= '0' && c <= '9')
                {
                    state = 58;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                break;
            case 57:
                if (c >= '0' && c <= '9')
                {
                    state = 58;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                break;
            case 58:
                if (c >= '0' && c <= '9')
                {
                    state = 59;
                }
                else
                {
                    // other condition
                    failState();
                    state = 0;
                    decForw(1);
                    lexemeStart = forward;
                    return ReturnTokenFactory(-1);
                }
                break;
            case 59:
                tk = TK_RNUM;
                r = ReturnTokenFactory(tk);
                decForw(1);
                state = 0;
                lexemeStart = forward;
                return r;
                break;
            case 60:
                tk = TK_NUM;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 61:
                tk = TK_NUM;
                decForw(1);
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 62:
                tk = TK_RNUM;
                r = ReturnTokenFactory(tk);
                state = 0;
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 63:
                if (c == '\n' || c == ' ' || c == '\t')
                {
                    state = 63;
                    if (c == '\n')
                    {
                        lineNumber++;
                    }
                }
                else
                {
                    state = 64;
                    decForw(1);
                }
                break;
            case 64:
                state = 0;
                r = ReturnTokenFactory(-3);
                decForw(1);
                lexemeStart = forward;
                return r;
                break;
            case 65:
                if (*forward != '\n')
                {
                    state = 66;
                }
                else
                {
                    state = 67;
                }
                break;
            case 66:
                if (*forward != '\n')
                {
                    state = 66;
                }
                else
                {
                    state = 67;
                }
                break;
            case 67:
                tk = TK_COMMENT;
                state = 0;
                r = ReturnTokenFactory(tk);
                lineNumber++;
                lexemeStart = forward;
                return r;
                break;
            default:
                return ReturnTokenFactory(-1);
                break;
            }
        }
    }
}

/*
    This function will be called to print all the tokens generated from the input source
    file on the console
*/
void printTokens()
{

    // printf("%-10s%-15s%s", "Line No.", "Token", "Lexeme");
    while (1)
    {
        returnToken r = getNextToken();
        if (r.flag != -2 && r.flag != -1)
        {
            if (r.flag == -3)
            {
                continue;
            }
            printf("\033[33m");
            printf("%*s", 20 - printf("Line no. %d", r.line), "");

            printf("\033[35m");
            printf("%*s", 20 - printf("Lexeme %s", r.lexeme), "");
            printf("\033[0m");

            printf("\033[36m");
            printf("Token %s \n", tokensArr[r.t]);
        }
        if (r.flag == -2)
        {
            break;
        }
    }
}

/**
 * The function takes the file name and internally creates a file pointer.
 * This file pointer is global and hence is not returned.
 */
void getStream(char *fileName)
{
    initializeBuffers(fileName);
    lexemeStart = (char *)malloc(sizeof(char));
    forward = (char *)malloc(sizeof(char));
    lexemeStart = buffer1;
    forward = buffer1;
    state = 0;
    lineNumber = 1;
    populateMap();
}
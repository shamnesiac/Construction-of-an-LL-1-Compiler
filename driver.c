/*
    GROUP 22 :
        ID : 2021B3A70995P | Name : Dhruv Ravi Krishnan
        ID : 2021B3A70981P | Name : Anirudh Anand
        ID : 2021B3A71738P | Name : Akshit Phophaliya
        ID : 2022A7PS1182P | Name : Arnav Dham
        ID : 2022A7PS0154P | Name : Shaurya Jain
        ID : 2022A7PS0187P | Name : Darsh Rathi
*/
#include "lexer.h"
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

GRAMMAR grammar_glob;
ProdRule ParseTable[NUM_NONTERMS][NUM_TERMS + 1];

int main(int argc, char *argv[])
{

    int choice = -1;
    grammar_glob = malloc(sizeof(grammar));
    parseFileGrammar("grammar.txt");
    FIRSTANDFOLLOW fnfset = computeFirstAndFollowSets();

    printf("\033[0;33m");
    printf("First and Follow Sets generated successfully\n");
    printf("Both Lexical and Syntax analyis modules implemented\n");
    printf("\033[0m");
    while (1)
    {

        printf("\033[0;36m");
        printf("\rPlease enter your choice: ");
        printf("\033[0m");
        scanf("%d", &choice);

        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            FILE *fp1 = (FILE *)malloc(sizeof(FILE));
            fp1 = fopen(argv[1], "r");
            // without comments source code is always saved in "WithouComment.txt"
            FILE *fp2 = (FILE *)malloc(sizeof(FILE));
            fp2 = fopen("WithoutComments.txt", "w+");
            removeComments(fp1, fp2);
            fclose(fp1);
            fclose(fp2);

            printf("\033[0;92m");
            printf("Comment removal successful. Output generated in 'WithoutComments.txt'\n");
            printf("\033[0m");
        }
        else if (choice == 2)
        {

            getStream(argv[1]);
            printTokens();
        }

        else if (choice == 3)
        {
            getStream(argv[1]);
            initialiseParseTable();
            createParseTable(fnfset);
            syncPopulateParseTable(fnfset);
            TREE_NODE one = parseInputSourceCode();
            printParseTree(one, argv[2]);
        }

        else if (choice == 4)
        {
            clock_t start_time, end_time;
            double total_CPU_time, total_CPU_time_in_seconds;
            start_time = clock();
            // invoke your lexer and parser here
            getStream(argv[1]);
            initialiseParseTable();
            createParseTable(fnfset);
            syncPopulateParseTable(fnfset);
            TREE_NODE one = parseInputSourceCode();
            printParseTree(one, argv[2]);
            end_time = clock();
            total_CPU_time = (double)(end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / CLOCKS_PER_SEC;
            // Print both total_CPU_time and total_CPU_time_in_seconds

            printf("\033[1;92m");
            printf("Total CPU time:");
            printf("\033[1;33m");
            printf(" %lf ", total_CPU_time);
            printf("\033[1;92m");
            printf("microsecond\nTotal CPU time in second:");
            printf("\033[1;33m");
            printf(" %lf\n", total_CPU_time_in_seconds);

            printf("\033[0m");
        }

        else
        {
            printf("\033[1;91m");
            printf("Incorrect choice - please enter choice from 0 to 4\n");
            printf("\033[0m");
        }
    }
    return 0;
}
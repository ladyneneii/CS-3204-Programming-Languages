#include <stdio.h>
#include <ctype.h>
#define MAX_LEXEME 100

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/* Function declarations */
void getChar(FILE *in_fp, char *nextChar, int *charClassPtr);
int lex(int *charClassPtr, char *nextChar, FILE *in_fp);
int lookup(char ch);
char addChar(int *lexLen, char ch, char lexeme[]);

int main() {
    FILE *in_fp, *fopen();
    int charClass;
    char ch;

    if ((in_fp = fopen("front.in", "r")) != NULL) {
        getChar(in_fp, &ch, &charClass);
        while(lex(&charClass, &ch, in_fp) != EOF) {}
    } else {
        printf("ERROR - cannot open front.in \n");
    }

    printf("Yessss");

    return 0;
}

/* getChar - a function to get the next character of input and determine its character class */
void getChar(FILE *in_fp, char *nextChar, int *charClassPtr) {
    if ((*nextChar = getc(in_fp)) != EOF) { 
        *charClassPtr = isalpha(*nextChar) ? LETTER :
                        (isdigit(*nextChar) ? DIGIT : UNKNOWN);

        // if (isalpha(*nextChar)) 
        //     *charClassPtr = LETTER;
        // else if (isdigit(*nextChar))
        //     *charClassPtr = DIGIT;
        // else 
        //     *charClassPtr = UNKNOWN;
    } else {
        *charClassPtr = EOF;
    }
}

/* addChar - a function to add nextChar to lexeme */
char addChar(int *lexLen, char ch, char lexeme[]) {
    if (*lexLen <= 98) {
        lexeme[(*lexLen)++] = ch;
        lexeme[*lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/* lex - a simple lexical analyzer for arithmetic expressions */
int lex(int *charClassPtr, char *nextChar, FILE *in_fp) {
    int nextToken, lexLen = 0;
    char lexeme[MAX_LEXEME];

    // skip whitespace characters
    while (isspace(*nextChar)){
        getChar(in_fp, nextChar, charClassPtr);
    }

    if (*charClassPtr == LETTER) {
        /* Parse identifiers */
        while (*charClassPtr == LETTER || *charClassPtr == DIGIT) {
            addChar(&lexLen, *nextChar, lexeme);
            getChar(in_fp, nextChar, charClassPtr);
        }
        nextToken = IDENT;
    } else if (*charClassPtr == DIGIT) { 
        /* Parse integer literals */
        while (*charClassPtr == DIGIT) {
            addChar(&lexLen, *nextChar, lexeme);
            getChar(in_fp, nextChar, charClassPtr);
        }
        nextToken = INT_LIT;
    } else if (*charClassPtr == UNKNOWN) {
        /* Parentheses and operators */
        nextToken = lookup(*nextChar);
        addChar(&lexLen, *nextChar, lexeme);
        getChar(in_fp, nextChar, charClassPtr);
    } else {
        /* EOF */
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);

    return nextToken;
} 

/* lookup - a function to lookup operators and parentheses and return the token */
int lookup(char ch) {
    switch (ch) {
        case '(': return LEFT_PAREN;
        case ')': return RIGHT_PAREN;
        case '+': return ADD_OP;
        case '-': return SUB_OP;
        case '*': return MULT_OP;
        case '/': return DIV_OP;
        default: return EOF;
    }
}
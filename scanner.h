#ifndef scanner_h
#define scanner_h

typedef struct {
    const char * start;
    const char * current;
    int line;
} Scanner;

typedef enum {
    //Single character tokens
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_COMMA, 
    //Double character tokens
    TOKEN_ASSIGN,
    //Literals
    TOKEN_IDENTIFIER, TOKEN_STRING,
    TOKEN_NUMBER,
    //Binary operators
    TOKEN_PLUS, TOKEN_MINUS,
    TOKEN_TIMES, TOKEN_DIVIDE, 
    //Keywords
    TOKEN_PRINT,
    //Extras
    TOKEN_EOF, TOKEN_ERROR 

} TokenType;

//Holds all of the individual tokens
typedef struct {
    TokenType type;
    const char * start;
    int length;
    int line;
} Token;



void initScanner(const char* source);
Token scanToken();

#endif
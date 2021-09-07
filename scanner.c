/*  This scanner is based on Robert Nystrom's Java
    implementation of a scanner for his Lox language.
    The language used for this scanner is a much simpler one,
    a straight line language, consisting only of:
    - Statements
    - Expressions
    - Expression Lists
    - Identifiers
    - Numbers
    Comments in this language will be C style, starting with '//'
*/

#include <string.h>

#include "scanner.h"
#include "util.h"

/*  Start is the point in the line which the scanner started to look
    ... at an individual token. It gets pushed forwards when a new token
    ... is looked at. 
    Current is the current place the scanner is looking at.

*/
Scanner scanner;

void initScanner(const char * source) {
   scanner.start = source;
   scanner.current = source;
   scanner.line = 1; 
}

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

static bool isAlpha(char c) {
    return  (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            c == '_';
}

static bool isAtEnd() {
    return *scanner.current == '\0';
}

//Advance simply returns the character it is on and moves the scanner to the next char
static char advance() {
    scanner.current++;
    return scanner.current[-1];
}

//Peek will return the current char, but DOESNT move on.
static char peek() {
    return *scanner.current;
}

//Peeknext checks the char in advance, and also DOESNT move on
static char peekNext() {
    if(isAtEnd()) return '\0';
    return scanner.current[1];
}

/*  In order to match for 2-character tokens, we simply check if
    ... the char for the token is what we expected. If its not, then
    ... it must be another 2-character token, or something different altogether
*/
static bool match(char expected) {
    if(isAtEnd()) return FALSE;
    if(*scanner.current != expected) return FALSE;
    scanner.current++;
    return TRUE;
}

/*  Since all the date from the token is pretty much contained in the scanner,
    we can take everything from it.
*/
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

static Token errorToken(const char * message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static void skipWhitespace() {
    for(;;) {
        char c = peek();
        switch(c) {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            //If we reach a new line we need to increment the scanners line
            case '\n':
                scanner.line++;
                advance();
                break;
            //Checking for comments here
            case '/':
                if(peekNext() == '/') {
                    //Just skip the whole line if you find a comment
                    while(peek() != '\n' && !isAtEnd()) advance();
                }
            default:
                return;
        }
    }
}

static TokenType checkKeyword(  int start, int length,
                                const char * rest, TokenType type) {
    if(scanner.current - scanner.start == start + length 
        && memcmp(scanner.start + start, rest, length) == 0) {
            return type;
        }
    return TOKEN_IDENTIFIER;
}


/*  Since theres only one keyword in the language atm "print"
    ... theres no need for a more complicated function, but as soon
    ... as the language needs more identifiers, we will use this.
*/
static TokenType identifierType() {
    switch(scanner.start[0]) {
        //The more keywords you have in the language, you simply add them here
        case 'p': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
    }
    return TOKEN_IDENTIFIER;
}

static Token number() {
    while(isDigit(peek())) advance();

    //Checking for float values
    if(peek() == '.' && isDigit(peekNext())) {
        //Once you see a dot, we advance over it 
        //and then check for the rest of the numbers
        advance();
        
        while(isDigit(peek())) advance();
    }
    return makeToken(TOKEN_NUMBER);
}

static Token identifier() {
    while(isAlpha(peek()) || isDigit(peek())) advance();
    return makeToken(identifierType());
}

Token scanToken() {
    scanner.start = scanner.current;

    if(isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();

    if(isAlpha(c)) return identifier();
    if(isDigit(c)) return number();

    switch(c) {
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case ',': return makeToken(TOKEN_COMMA);
        case '+': return makeToken(TOKEN_PLUS);
        case '-': return makeToken(TOKEN_MINUS);
        case '*': return makeToken(TOKEN_TIMES);
        case '/': return makeToken(TOKEN_DIVIDE);

    }

    return errorToken("Unexpected character.");
}

//Going to have to see where this fits
void afterInitScanner() {
    int line = -1;
    for(;;) {
        Token token = scanToken();
        if(token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("    | ");
        }
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if(token.type == TOKEN_EOF) break;
    }
}

static void runFile(const char * path) {
    //FILL IN THIS FUNC
}

/*  Repl will be the default action for the scanner. We take in lines 
    ... one by one and scan them for tokens.
*/
static void repl() {
    //We only handle one line at a time because we are lazy
    char line[1024];
    for(;;) {
        printf("> ");
    
        if(!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        initScanner(line);
        int line = -1;

        for(;;) {
            Token token = scanToken();
            if(token.line != line) {
                printf("%4d ", token.line);
                line = token.line;
            } else {
                printf("    | ");
            }
            printf("%2d '%.*s'\n", token.type, token.length, token.start);

            if(token.type == TOKEN_EOF) break;
        }
    }
}


/*  If there are no arguments, we send the scanner to read input from the user line by line
    If a file is supplied, we read through it to split it into tokens

*/
int main(int argc, const char * argv[]) {
    
    
    if (argc == 1) {
        repl();    
    } else if(argc == 2) {
        runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: scanner [path]\n");
        exit(64);
    }
}
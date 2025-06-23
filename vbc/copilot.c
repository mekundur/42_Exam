#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

const char *input;

void unexpected(const char *msg, char token)
{
    if (token)
        printf(msg, token);
    else
        printf("Unexpected end of input\n");
    exit(1);
}

char peek() {
    return *input;
}

char consume() {
    return *input++;
}

int expr();

int factor() 
{
    char c = peek();
    if (isdigit(c)) 
    {
        return *input++ - '0';
    } 
    else if (c == '(') 
    {
        consume(); // consume '('
        int val = expr();
        if (peek() != ')')
            unexpected("Unexpected token '%c'\n", peek() ? peek() : 0);
        consume(); // consume ')'
        return val;
    } else if (c == '\0') {
        unexpected(NULL, 0);
    } else {
        unexpected("Unexpected token '%c'\n", c);
    }
    return 0; // unreachable
}

int term() {
    int val = factor();
    while (peek() == '*') {
        consume();
        val *= factor();
    }
    return val;
}

int expr() {
    int val = term();
    while (peek() == '+') {
        consume();
        val += term();
    }
    return val;
}

int main(int argc, char **argv) 
{
    if (argc != 2)
        return 1;
    input = argv[1];
    int result = expr();
    if (*input != '\0')
        unexpected("Unexpected token '%c'\n", *input);
    printf("%d\n", result);
    return 0;
}

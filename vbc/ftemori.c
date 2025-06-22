#include <stdlib.h>
#include <stdio.h>

void error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int parse_expression();
const char *input;
int pos = 0;

char curr()
{
    return input[pos];
}

void step()
{
    pos++;
}

int parse_atom()
{
    char c = curr();
    if (c >= '0' && c <= '9')
    {
        step();
        return (int)(c - '0');
    }
    if (c == '(')
    {
        step();
        int result = parse_expression();
        if (curr() != ')')
        error("Unexpected symbol: Expected ')'");
        step();
        return result;
    }
    error("Unexpected symbol");
    return 0;
}

int parse_mul()
{
    int result = parse_atom();
    while(curr() == '*')
    {
        step();
        result *= parse_atom();
    }
    return(result);
}

int parse_expression()
{
    int result = parse_mul();
    while(curr() == '+')
    {
        step();
        result += parse_mul();
    }
    return (result);
}

int eval_expression()
{
    int result = parse_expression();
    if (curr() != '\0')
    {
        if (curr() == ')')
            error("extra parenthesis: ')'");
        else
            error("Unexpected end of input");
    }
    return (result);
}

int main(int argc, char *argv[])
{
    input = argv[1];
    if (argc != 2) 
        return fprintf(stderr, "Usage: %s \"expression\"\n", argv[0]), 1;
    printf("Result: %d\n", eval_expression());
    return 0;
}

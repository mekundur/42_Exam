#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

const char *input;

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
	exit(1);
}

int expr();

int factor() 
{
	char c = *input;
	
	if (isdigit(c)) 
		return *(input++) - '0';	
	else if (c == '(') 
	{
        	input++; // consume '('
        	int val = expr();
        	if (*input != ')')
            	unexpected(*input ? *input : 0);
        	input++; // consume ')'
        	return val;
   	}
	else
		unexpected(*input);
	return 0;
}

int multi()
{
	int val = factor();

	while (*input == '*') 
	{
        	input++;
       		val *= factor();
    	}
    	return val;
}

int expr()
{
	int val = multi();
	
	while (*input == '+') 
	{
        	input++;
        	val += multi();
	}
	return val;
}

int main(int argc, char **argv) 
{
	if (argc != 2)
        	return 1;
   	input = argv[1];
    
	int result;
	result = expr();

	if (*input != '\0')
		unexpected(*input);
 	printf("%d\n", result);
	return 0;
}

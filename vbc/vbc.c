#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "ctype.h"

const char *s;

void	unexpected(char c)
{
	if (c)
		printf("Unexpected token '%c'\n", c);
	else
		printf("Unexpected end of input\n");
	exit (1);
}

int	expr();

int	factor()
{
	int	val = 0;

	if (isdigit(*s))
		val = *s++ - 48;
	else if (*s == '(')	
	{
		s++;
		val = expr();
		if (*s != ')')
			unexpected(*s);
		s++;
	}
	else
		unexpected(*s);
	
	return val;
}

int	multi()
{
	int 	val = factor();

	while (*s == '*')
	{
		s++;
		val *= factor();
	}
	return val;
}


int	expr()
{
	int	val = multi();
	
	while (*s == '+')
	{
		s++;
		val += multi();
	}
	return val;
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	s = argv[1];

	int val = expr();

	if (*s)
		unexpected(*s);
	printf("%d\n", val);
	return 0;

}

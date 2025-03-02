#include <stdio.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	ft_printout(int len, char str[len], char index[len], int *max)
{
	int	i;
	int	printed;
	int	num;


	printed = 0;
	num = 0;
	i = 0;
	while (str[i])
	{
		if (index[i] == 1)
			num++;
		i++;	
	}	
	if (num < *max)
		return ;
	i = 0;
	while (index[len - 1 - i] != 1)
		i++;
	if (str[len - 1 - i] == '(')
		return ;
	
//	printf("i: %d\n", i);

//	write(1, "*****SOL: ", 10);
	i = 0;
	while (str[i])
	{
		if (index[i] == 1)
		{
			write(1, &str[i], 1);
			printed++;
		}
		else
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	if (printed > *max)
		*max = printed;
//	printf("num: %d\n", num);
//	printf("max: %d\n", *max);
}

void	rip(int	len, char str[len], int i, int left, int right, char index[len], int *max)
{
	while (str[i])
	{
		if (str[i] == '(')
		{
			left++;
			index[i] = 1;
		}
		else if (str[i] == ')')
		{
			right++;
			index[i] = 1;
		}
		
		rip(len, str, i + 1, left, right, index, max);
		
//		printf("i: %d\n", i);
//		printf("left: %d\n", left);
//		printf("right: %d\n", right);

		if (left == right && left > 0 && right > 0)
			ft_printout(len, str, index, max);

		if (str[i] == ')')
		{
			right--;
			index[i] = 0;
		}
		else if (str[i] == '(')
		{
			left--;
			index[i] = 0;
		}
	
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	int	i;
	int	len;
	static int	max = 0;

	len = ft_strlen(argv[1]);
	char	str[len];
	i = 0;
	while(argv[1][i])
	{
		str[i] = argv[1][i];
		i++;
	}
	str[i] = 0;
//	puts(str);
	
	// initialize index array 
	// for printing purpose
	char	index[len];
	i = 0;
	while (i < len)
		index[i++] = 0;
	
	// trim '(' from the end of the input
	int	j = 0;
	while (len > 0 && str[len - 1 - j] == '(')
	{
		str[len-1-j] = 0;
		j++;
	}
	// trim '(' from the start of the input
	i = 0;
	while (str[i] && str[i] == ')')
		i++;

//	puts(str + i);
	len = len - i - j;
//	printf("len: %d\n", len);
	rip(len , str + i, 0, 0, 0, index, &max);
}

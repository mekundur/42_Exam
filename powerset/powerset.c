#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void	print_subset(int qty, int s[qty], bool index[qty])
{
	int	i;
	int	last;

	i = 0;
	while(i < qty)
	{
		if (index[i] == 1)
			last = i;	
		i++;
	}
	
	i = 0;
	while(i < qty)
	{
		if (i == last)
			fprintf(stdout, "%d", s[i]);
		else if (index[i] == 1)
			fprintf(stdout, "%d ", s[i]);
		i++;
	}
	fprintf(stdout, "\n");
}

void	iter(int n, int qty, int s[qty], int total, int i, bool index[qty])
{
	while (i < qty)
	{
		total -= s[i];
		index[i] = 1;
		if (total == 0)
			print_subset(qty, s, index);
		iter(n, qty, s, total, i + 1, index);
		//backtracking:
		total += s[i];
		index[i] = 0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (0);

	int	n = atoi(argv[1]);
	int	qty = argc - 2;
	int	s[qty];
	bool	index[qty];
	int	i;

	i = 0;
	while (i < qty)
	{
		s[i] = atoi(argv[i + 2]);
		i++;
	}
	
	i = 0;
	while (i < qty)
		index[i++] = 0;
	
	iter(n, qty, s, n, 0, index);

	if (n == 0)
		fprintf(stdout, "\n");

}

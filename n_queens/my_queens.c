#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "unistd.h"

void	print_board(int n, char board[n][n])
{
	int	i = 0;
	int	j = 0;

//	printf("n: %d\n", n);
	while (j < n)
	{
		i = 0;
		while (i < n)
		{
		//	if (board[i][j] == 0)
		//		printf(". ");
			if (board[i][j] == 'Q')
				printf("%d ", i);
			i++;
		}
		//printf("\n");
		j++;
	}
	printf("\n");
}	

bool	is_safe(int n, char board[n][n], int row, int col)
{
	int	i;
	int	j;
	
	// diagonal check upper left
	i = row;
	j = col;
	while (i >= 0 && j >= 0)
	{
		if (board[i][j] == 'Q')
			return (false);
		//	return (write(1, "diaL\n", 5), false);
		i--;
		j--;
	}

	// diagonal check upper right
	i = row;
	j = col;
	while (i >= 0 && j < n)
	{
		if (board[i][j] == 'Q')
			return (false);
		//	return (write(1, "diaR\n", 5), false);
		j++;
		i--;
	}

	// vertical check
	i = row;
	j = col;
	while (i >= 0)
	{
		if (board[i][j] == 'Q')
			return (false);
		//	return (write(1, "Vert\n", 5), false);
		i--;
	}
	return (true);
}

void	find_solution(int n, char board[n][n], int row, int queen)
{
	int	col = 0;
		
//	printf("ROW: %d\n", row);
	if (row == n)
		print_board(n, board);
		
	col = 0;
	while (col < n)
	{
		if (is_safe(n, board, row, col))
		{
			board[row][col] = 'Q';
		//	print_board(n, board);
			find_solution(n, board, row + 1, queen);
		}	
		board[row][col] = 0;
		col++;
	}
}

int	main(int argc, char **argv)
{
	int	n;

	if(argc != 2)
		return(0);
	n = atoi(argv[1]);
//	printf("n: %d\n", n);
	if (n > 0)
	{
		char	board[n][n];
		memset(board, 0, n * n * sizeof(char));
//		print_board(n, board);
		find_solution(n, board, 0, 0);
	}
}

#include "stdio.h"
#include "stdlib.h"



bool	is_safe()
{
	




	return (TRUE);
}

void	find_solution(int board[n][n], int row)
{
	int	col = 0;
	
	while (col < n)
	{
		if (is_safe(board, row))

	
	
	
		col++;
	}



}



int	main(int argc, char **argv)
{
	int	n;

	n = 0;
	if(argc != 2)
		return(0);
	
	n = atoi(argv[1]);
	int	board[n][n] = {0};
	find_solution(board, 0);

}

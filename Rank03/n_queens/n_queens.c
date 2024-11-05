/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:49:41 by mekundur          #+#    #+#             */
/*   Updated: 2024/11/04 18:42:03 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void	print_board(char *board, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			printf("%c ", board[i * n + j]);	
			j++;
		}
		printf("\n");	
		i++;
	}
	printf("\n");	
}

char	*board_init(char *board, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			board[i * n + j] = '_';
			j++;
		}
		i++;
	}
	return (board);
}

char	*horizontal_mask(char *board, int i, int n)
{
	int	j;

	j = 0;
	while (j < n)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		j++;
	}
	return(board);
}

char	*vertical_mask(char *board, int j, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		i++;
	}
	return(board);
}

char	*diagonal_mask(char *board, int i, int j, int n)
{
	int	tmpi;
	int	tmpj;

	tmpi = i;
	tmpj = j;
	while (i < n && j < n)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		j++;
		i++;
	}
	i = tmpi;
	j = tmpj;
	while (i >= 0 && j >= 0)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		i--;
		j--;
	}
	i = tmpi;
	j = tmpj;
	while (i >= 0 && j < n)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		i--;
		j++;
	}
	i = tmpi;
	j = tmpj;
	while (i < n && j >= 0)
	{
		if (board[i * n + j] != 'Q')		
			board[i * n + j] = 'x';		
		i++;
		j--;
	}
	return (board);
}

char	*put_queens(char *board, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n)
		{
			while (board[i * n + j] == 'x' || board[i *n + j] == 'Q')
				j++;
			board[i * n + j] = 'Q';
			board = horizontal_mask(board, i, n);
			board = vertical_mask(board, j, n);
			board = diagonal_mask(board, i, j, n);
			print_board(board, n);
		}
		i++;
	}
	return(board);
}

int	main(int argc, char **argv)
{
	int	n;
	char	*board;
	if (argc != 2)
		return (0);

	n = atoi(argv[1]);
	printf("n: %d\n", n);
	board = (char *)malloc(n * n * sizeof(char));
	printf("board_size: %lu\n", sizeof(board));
	printf("board_size: %lu\n", sizeof(*board));

	board = board_init(board, n);
	board = put_queens(board, n);

}

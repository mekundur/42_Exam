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
			board[i * n + j] = '0';
			j++;
		}
		i++;
	}
	return (board);
}

char	*horizontal_mask(char *board, int i, int j, int n)
{
	while (j < n)
	{
		board[i * n + j] = '-';		
		j++;
	}
	return(board);
}

char	*vertical_mask(char *board, int i, int j, int n)
{
	while (i < n)
	{
		board[i * n + j] = '-';		
		i++;
	}
	return(board);
}

char	*diagonal_mask(char *board, int i, int j, int n)
{
	while (i < n && j < n)
	{
		board[i * n + j] = '-';	
		j++;
		i++;
	}
	return (board);
}

char	*put_queens(char *board, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (i < n)
	{
		j = 1;
		while (j < n)
		{
			board[i * n + j] = 'X';
			board = horizontal_mask(board, i, j + 1, n);
			board = vertical_mask(board, i + 1, j, n);
			print_board(board, n);
			board = diagonal_mask(board, i + 1, j + 1, n);
			print_board(board, n);
		}
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
	print_board(board, n);	
	board = put_queens(board, n);
	print_board(board, n);	

}

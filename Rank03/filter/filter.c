/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekundur <mekundur@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:32:14 by mekundur          #+#    #+#             */
/*   Updated: 2024/10/25 22:43:39 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#define	BUF 5

int main(int argc, char **argv)
{
	int	x;
	int	i;
	int	len;
	char	*buf;
	char	*tmp;
	char	*str;
	char	*ptr;

	ptr = 0;
	str = 0;
	buf = 0;
	tmp = 0;
	x = 1;
	i = 0;
	if (argc != 2)
		return (0);
	while(x)
	{
		printf("__Iteration_%d__\n", i);
		tmp = str;
		printf("tmp: %s\n", tmp);
		buf = (char *)calloc((BUF + 1), sizeof(char));
		x = read(0, buf, BUF);
		printf("buf: %s\n", buf);

		if (x == -1)
			stderr;
		str = (char *)calloc((i * BUF + 1), sizeof(char));
		memmove(str, tmp, i * BUF);
		memmove(str + i * BUF, buf, x);
		free(tmp);
		free(buf);
		printf("str: %s\n", str);
		printf("len_str %ld\n", strlen(str));
		printf("x: %d\n", x);
		i++;
		if (x < BUF)
		{
	//		ptr = 0;
	//		len = strlen(argv[1]);
	//		ptr = memmem(str, strlen(str), argv[1], len);
	//		while (ptr && len-- > 0)
	//			*(ptr++) = '*';
			write(1, str, strlen(str));
		}	
	}
	return (free(str), 0);
}


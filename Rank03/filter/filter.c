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

#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#define	BUF 10


int main(int argc, char **argv)
{
	int	x;
	char	*buf;
	char	*tmp;
	
	char	*str;
	char	*ptr;

	str = 0;
	buf = 0;
	tmp = 0;
	x = 0;
	if (argc != 2)
		return (0);

	while(x)
	{
		tmp = str;
		buf = (char *)calloc((BUF + 1), sizeof(char));
		x = read(0, buf, BUF);
		if (x == -1)
		{
			stderr;
		}
		else if (x == 0)
		       break;	
		str = (char *)calloc((strlen(tmp) + strlen(buf) + 1), sizeof(char));
		memmove(str, tmp, strlen(tmp));
		memmove(str + strlen(tmp), buf, strlen(buf));
		free(tmp);
		free(buf);
	}
	printf("tmp: %s\n", tmp);
	printf("buf: %s\n", buf);
	printf("str: %s\n", str);
	ptr = memmem(str, strlen(str), argv[1], strlen(argv[1]));


	return (free(str), 0);
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int	ft_strlen(char *s)
{
	int len = 0;

	while (s && s[len])
		len++;
	return (len);
}

void	ft_strcpy(char	*dst, char *src)
{
	int	i = 0;

	while (src && dst && src[i])
	{
		dst[i] = src[i];
		i++;
	}
}

void	store_floats(char **values, int i)
{
	float	coor;

	

}

int	main(int argc, char **argv)
{
	FILE *file;
	ssize_t	byte = 0;
	size_t	n = 1;
	size_t	*ptr = &n;
	char	**lineptr;

	int	i = 0;

	lineptr = (char **)malloc(sizeof(char *));
	lineptr[0] = (char*)malloc(10 * sizeof(char));

//	printf("argv[1]: %s\n", argv[1]);
	file = fopen(argv[1], "r");
	printf("file: %p\n", file);
	printf("&file: %p\n", &file);

	while (byte != -1)
	{
		byte = getline(lineptr, ptr, file);
		if (byte == -1)
			break;

		printf("n: %ld\n", n);
		printf("bytes_read: %ld\n", byte);
		printf("line_read: %s", lineptr[0]);

		i++;
	}
	fclose(file);

	char	**values;
	values = (char **)malloc((i + 1) * sizeof(char *));
	
	while (values && i >= 0)
	{
		values[i--] = NULL;
	}
	i = 0;
	while(values && values[i])
	{
		printf("values[%d]: %s\n", i, values[i]);
		i++;
	}
	
	file = fopen(argv[1], "r");

	i = 0;
	byte = 0;
	while (byte != -1)
	{
		byte = getline(lineptr, ptr, file);
		if (byte == -1)
			break;
		values[i] = (char *)malloc(ft_strlen(lineptr[0]) + 1);
		strcpy(values[i], *lineptr);	
		printf("n: %ld\n", n);
		printf("bytes_read: %ld\n", byte);
		printf("line_read: %s", lineptr[0]);
		printf("values[i]: %s", values[i]);
		i++;
	}
	if (lineptr[0])
			free(lineptr[0]);
	printf("i: %d\n", i);
	
	i = 0;
	while(values && values[i])
	{
		printf("values[%d]: %s\n", i, values[i]);
		i++;
	}

	i = 0;
	while (values && values[i])
	{
		if (values[i]);	
			free(values[i]);
		i++;
	}

	store_floats(values);

	free(values);
	free(lineptr);
	fclose(file);

}

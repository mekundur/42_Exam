#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

int	ft_factorial(int n)
{
	int	result = 1;
	
	if (n == 0)
		return (0);
	while (n > 1){
		result *= n;
		n--;	
	}
	return(result);
}

int	ft_strlen(char *s)
{
	int len = 0;

	while (s && s[len])
		len++;
	return(len);
}

int	ft_strchr(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

void	ft_strcpy(char *dst, char *src)
{
	int	i = 0;

	while (dst && src && src[i])
	{
		dst[i] = src[i];
		i++;	
	}
}

void	ft_swap(char *c, char *s)
{
	char tmp;

	tmp = *c;
	*c = *s;
	*s = tmp;
}

char	*ft_strcmp(char *s1, char *s2)
{
	int	i = 0;
	while (s1 && s2 && s1[i] && s2[i])
	{
		if(s1[i] < s2[i])
			return s1;
		else if (s1[i] > s2[i])
			return s2;
		i++;
	}	
	return 0;
}

void	permute(int len, char **perms, char set[len+1], int left, int right, int *index)
{
	int	i;

	if (left == right)
	{
		perms[*index] = (char *)malloc((len + 1) * sizeof(char));
		ft_strcpy(perms[*index], set);
//		printf("SAVED_set: %s\n\n", perms[*index]);
		(*index)++;
		return ;
	}
	i = left;
	while (i <= right)
	{
//		printf("org_set: %s\n", set);
		ft_swap(&set[i], &set[left]);
//		printf("swap_set: %s\n", set);
		permute(len, perms, set, left + 1, right, index);
		ft_swap(&set[i], &set[left]);
//		printf("back_set: %s\n\n", set);
		i++;
	}

}

int main(int argc, char **argv)
{
	int	len = 0;
	int	total = 0;
	int	i = 0;
	int	index = 0;

	if (argc != 2)
		return (0);

	len = ft_strlen(argv[1]);
	total = ft_factorial(len);
	char set[len + 1];
	set[len] = 0;
	ft_strcpy(set, argv[1]);
//	printf("set: %s\n", set);
//	printf("Total: %d\n", total);
	
	char	**perms = NULL;
	perms = (char **)malloc(total * sizeof(char *));
	
	permute(len, perms, set, 0, len - 1, &index);

	i = 0;
	while (perms && perms[i])
	{
		printf("%d: %s\n", i + 1, perms[i]);
		i++;
	}
	i = 0;
	while (i < total)
		free(perms[i++]);
	free(perms);
}

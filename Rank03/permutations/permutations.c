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

void	put_permutations(int total, int len, char **perm, char *set, int i, int j, int k)
{
//	int	j = 0;
//	int	k = 0;

//	if (i >= len)
//		i = i % len;	
	while (k < total)
	{
	//	i = 0;
		while (ft_strlen(perm[k]) < len && i < len)
		{	
			if (!ft_strchr(perm[k], set[j]) && j < len)
			{
				perm[k][i] = set[j];
				put_permutations(total, len, perm, set, i + 1, (j + 1) % len, k + 1);
			}
			else
			{
			//	if (i >= len)
			//		i = i % len;	
			//	j = (j + 1) % len;
				i++;	
			}
		}
//		printf("%d: %s\n", k, perm[k]);
		k++;
	}

}

int main(int argc, char **argv)
{
	char	*set;
	int	len = 0;
	int	total = 0;
	int	i = 0;
	int	j = 0;

	if (argc != 2)
		return (0);
	set = argv[1];
	len = ft_strlen(set);
	total = ft_factorial(len);

	printf("Total: %d\n", total);
	
	char	**perm = NULL;
	perm = (char **)malloc(total * sizeof(char *));
	
	i = 0;
	while (i < total)
		perm[i++] = (char *)calloc((len + 1), sizeof(char));
	
	put_permutations(total, len, perm, set, 0, 0, 0);
	

	i = 0;
	while (i < total)
		printf("%d: %s\n", i, perm[i++]);

	i = 0;
	while (i < total)
		free(perm[i++]);
	free(perm);
}

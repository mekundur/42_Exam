#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "get_next_line.h"

// SOLUTION THAT WORKED IN THE EXAM!

int	ft_popen(char const *file, char *const argv[], char type)
{
	int	fd[2];
	pipe(fd);
	if (type == 'r')
	{
		if (!fork())
		{
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			execvp(file, argv);	
			exit(1);	
		}
		close(fd[1]);
		return(fd[0]);
	}	
	else if ((type) == 'w')
	{
		if(!fork())
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);	
			exit(1);	
		}
		close(fd[0]);
		return(fd[0]);	
	}
	else
		return (0);
}

int	main(void)
{
	char	*line;
	FILE	*file;

//	file = popen("ls", "r");
//	getline(&line, NULL, file);
	
	int	fd = ft_popen("ls", (char *const[]){"ls", "-l", NULL}, 'r');
	printf("fd: %d\n", fd);
	line = get_next_line(fd);
	
	puts(line);

		
//	int	fd = ft_popen("who", (char *const[]){"who", NULL}, 'w');



}


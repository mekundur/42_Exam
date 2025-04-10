#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{	
	char	***tmp;
	int	i;
	int	j;
	int	num = 0;
	int	pfd[2];
	int	cfd1;
	int	cfd2;

	i = 0;
	while (cmds && cmds[i])
		i++;
	num = i;
	printf("%d\n", num);

/*	tmp = cmds;
	i = 0;
	while (tmp && tmp[i])
	{
		j = 0;
		while (tmp[i][j])
		{
			dprintf(2, "%s ", tmp[i][j]);
			j++;
		}
		dprintf(2, "\n");
		i++;
	}
*/
	pipe(pfd);
	i = 0;
	while (cmds && cmds[i])
	{
		cfd2 = fork();
		if (cfd1 == 0)
		{
			dup2(pfd[1], 1);
			execvp(cmds[i][0], cmds[i]);		
			close(pfd[0]);
			close(pfd[1]);
		}	
		i++;
		cfd2 = fork();
		if (cfd2 == 0)
		{
			dup2(pfd[0], 0);
			execvp(cmds[i][0], cmds[i]);		
			close(pfd[0]);
			close(pfd[1]);
		}
		i++;
	}
	wait(NULL);
	wait(NULL);
	close(pfd[0]);
	close(pfd[1]);
	return (0);
}

int	main(int argc, char **argv)
{
	int	cmd_size = 1;

	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "|"))
			cmd_size++;
	}
	char	***cmds = calloc(cmd_size + 1, sizeof(char *));
	if (!cmds)
	{
		dprintf(2, "Malloc error\n");
		return 1;
	}
	cmds[0] = argv + 1;
	int cmds_i = 1;
	for (int i = 1; i < argc; i++)
		if (!strcmp(argv[i], "|"))
		{
			cmds[cmds_i] = argv + i + 1;
			argv[i] = NULL;
			cmds_i++;
		}
	printf("%d\n", cmds_i);
	int ret = picoshell(cmds);
	if (ret)
		perror ("picoshell");
	free (cmds);
	return ret;
}

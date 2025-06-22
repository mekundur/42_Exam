#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	picoshell(char **cmds[])
{	
	int	i = 0;
	int	num = 0;
	int	pfd[2];
	int	prev = 0;

	while (cmds && cmds[num])
		num++;
	i = 0;
	//while (cmds && cmds[i])
	while (i < num)
	{
		pipe(pfd);
		if(!fork())
		{
			if (prev){
				dup2(prev, 0);
				close(prev);
			}
			if (i < (num - 1))
				dup2(pfd[1], 1);
			close(pfd[0]);
			close(pfd[1]);	
			execvp(cmds[i][0], cmds[i]);		
		}
		prev = pfd[0];
		// close(pfd[0]); // when this is kept and command is more than 2 program kept hanged
		close(pfd[1]);
		i++;
	}
	while (wait(NULL) > 0)
		;
	for (i=0; i < 3 + num; i++)
		close(i);
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
//	printf("%d\n", cmds_i);
	int ret = picoshell(cmds);
	if (ret)
		perror ("picoshell");
	free (cmds);
	return ret;
}

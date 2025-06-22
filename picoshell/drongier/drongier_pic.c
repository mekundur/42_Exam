#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int picoshell(char **cmds[])
{
	int i;
	int prev_fd;
	pid_t pid;
	int fd[2];
	i = 0;
	prev_fd = 0;
	while(cmds[i])
	{
		if(cmds[i+1])
			pipe(fd);
		pid = fork();
		if(pid == 0)
		{
			if(prev_fd !=0)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if(cmds[i+1])
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			execvp(cmds[i][0], cmds[i]);
			exit(1);
		}
		else
		{
			if(prev_fd !=0)
				close(prev_fd);
			if(cmds[i+1])
			{
				close(fd[1]);
				prev_fd = fd[0];
			}
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	return (0);
}

int     main(int argc, char **argv)
{
        int     cmd_size = 1;

        for (int i = 1; i < argc; i++)
        {
                if (!strcmp(argv[i], "|"))
                        cmd_size++;
        }
        char    ***cmds = calloc(cmd_size + 1, sizeof(char *));
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
//      printf("%d\n", cmds_i);
        int ret = picoshell(cmds);
        if (ret)
                perror ("picoshell");
        free (cmds);
        return ret;
}

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

/**
 * test with
 * valgrind --trace-children=yes --track-fds=all
 * as we are not allowed to use free there will be leaks in the child
 * caused by char ***cmds (inherited indirectly from main)
 * 
 * compile
 * cc -Wall -Werror -Wextra picoshell.c main.c -o picoshell
 */

//not required
/*
int	ft_cmd_count(char **cmds[])
{
	int	i;

	i = 0;
	while (cmds[i])
		i += 1;
	return (i);
}
*/

int	picoshell(char **cmds[])
{
	int	i;
	int	pipefd[2];
	// int	cmd_count;
	int	wstatus;
	int	exit_status;
	//int	prev_fd; //not necessary if read-end of pipe is sent to stdin each time
	pid_t	pid;

	i = 0;
	wstatus = -11;
	exit_status = -22;
	//prev_fd = 0;
	// cmd_count = ft_cmd_count(cmds);
	//if (pipe(pipefd) == -1) //does not work as we get race conditions if we do not create a new pipe for each fork
		//return (1);
	while (cmds[i])
	{
		if (cmds[i + 1])
			if (pipe(pipefd) == -1)
				return (1);
		//printf("cmd: %s\n", cmds[i][0]);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
	//		if (i > 0)
	//		{
	//			dup2(prev_fd, 0);
	//			close(prev_fd);
	//		}
			close(pipefd[0]);
			//if (i < cmd_count - 1)
			if (cmds[i + 1])
				dup2(pipefd[1], 1);
			close(pipefd[1]);
			if (execvp(cmds[i][0], cmds[i]) < 0)
				return (1);
		}
		else
		{
	//		if (prev_fd)
	//			close(prev_fd);
			if (cmds[i + 1])
			{
				close(pipefd[1]);
	//			prev_fd = pipefd[0];
				dup2(pipefd[0], 0);
				close(pipefd[0]);
			}
		}
		i += 1;
	}
	while (wait(NULL) > 0)
		;
	//close(pipefd[0]);
	//close(pipefd[1]);
	return (0);
	// i = 0;
	// while (i < cmd_count)
	// {
		// if (waitpid(pid, &wstatus, 0))
		// {
		// 	if (WIFEXITED(wstatus))
		// 		exit_status= WEXITSTATUS(wstatus);
		// }
	// }
	//not necessary:
//	if (exit_status == 0)
//		return (0);
//	else
//		return (1);
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

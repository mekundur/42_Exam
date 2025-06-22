#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	int	status;
	pid_t	child;
	int	signal;
	unsigned int	time = 0;

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0) {
		f();
		exit(0);
	}
	while (1){
		if (!waitpid(child, &status, WNOHANG)) {
			if (time >= timeout) {
				kill(child, 9);
				waitpid(child, &status, 0);
				if (verbose)
					printf("Bad function: timed out after %d seconds\n", timeout);
				return(0);
			}
			sleep(1);
			time++;
		}
		else if (WIFEXITED(status)) {
			status = WEXITSTATUS(status);
			if (status && verbose)
				printf("Bad function: exited with code %d\n", status);
			else if (status == 0) {
				if (verbose)
					printf("Nice function!\n");
				return (1);
			}
			return (0);
		}
		else if (WIFSIGNALED(status)) {
			signal = WTERMSIG(status);
			if (signal == SIGALRM && verbose)
				printf("Bad function: timed out after %d seconds\n", timeout);
			else if (signal && verbose)
				printf("Bad function: %s\n", strsignal(signal));
			return (0);
		}
	}
	return (0);
}

// Test functions:
void nice_function(void) {return ;}
void nonzero_exit_function(void) {exit(42);}
void segfault_function(void) {int *p = NULL; *p = 123;}  // Causes SIGSEGV
void abort_function(void) {abort();}  // Causes SIGABRT
void timeout_function(void) {sleep(5);}  // Should timeout if timeout < 5
void check_zombies(void) {
    FILE *fp = popen("ps -eo pid,ppid,state,comm | grep Z", "r");
    if (!fp) return;

    char buf[256];
    printf("Zombie processes:\n");
    while (fgets(buf, sizeof(buf), fp)) {
        printf("%s", buf);
    }
    pclose(fp);
}

void	f6(void)
{
	printf("-> I will run forever and ignore all signales!\n");
	sigaction(SIGALRM, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGINT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGTERM, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGSEGV, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGPIPE, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGBUS, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGCHLD, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGHUP, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGTSTP, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGTTIN, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGTTOU, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGURG, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
	while (true) {}
}

int main(void) 
{
   	printf("return: %d\n", sandbox(nice_function, 2, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(nice_function, 2, false));
	check_zombies();
	printf("return: %d\n", sandbox(nonzero_exit_function, 3, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(nonzero_exit_function, 2, false));
	check_zombies();
	printf("return: %d\n", sandbox(segfault_function, 2, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(segfault_function, 2, false));
	check_zombies();
	printf("return: %d\n", sandbox(abort_function, 2, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(abort_function, 2, false));
	check_zombies();
	printf("return: %d\n", sandbox(timeout_function, 2, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(timeout_function, 2, false));
	check_zombies();
	printf("return: %d\n", sandbox(f6, 2, true));
	check_zombies();
	printf("false\nreturn: %d\n", sandbox(f6, 2, false));
	check_zombies();
	return 0;
}


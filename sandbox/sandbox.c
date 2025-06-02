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

	child = fork();
	if (child < 0)
		return (-1);
	if (child == 0) {
		alarm(timeout);
		f();
		printf("CHILD\n");
		exit(0);
	}
	waitpid(child, &status, 0);
//	printf("STATUS: %d\n", status);
	if (WIFEXITED(status)) {
		status = WEXITSTATUS(status);
		if (status && verbose)
			printf("Bad function: exited with code %d\n", status);
		else if (status == 0 && verbose) {
			printf("Nice function!\n");
			return (1);
		}
		else if (status == 0)
			return(1);
	}
	else if (WIFSIGNALED(status)) {
		signal = WTERMSIG(status);
		if (signal == SIGALRM && verbose)
			printf("Bad function: timed out after %d seconds\n", timeout);
		else if (signal && verbose)
			printf("Bad function: %s\n", strsignal(signal));
	}
	return (0);
}

// Test functions:

void nice_function(void) {
	//exit(0);
	return ;
}

void nonzero_exit_function(void) {
    exit(42);
}

void segfault_function(void) {
    int *p = NULL;
    *p = 123;  // Causes SIGSEGV
}

void abort_function(void) {
    abort();  // Causes SIGABRT
}

void timeout_function(void) {
    sleep(5);  // Should timeout if timeout < 5
}


// Check for zombie children:

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

int main(void) 
{
       	printf("return: %d\n", sandbox(nice_function, 2, true));
 	check_zombies();
       	printf("false\nreturn: %d\n", sandbox(nice_function, 2, false));
 	check_zombies();
 	printf("return: %d\n", sandbox(nonzero_exit_function, 2, true));
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
	return 0;
}


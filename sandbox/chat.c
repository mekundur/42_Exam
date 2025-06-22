#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

// The sandbox function
int sandbox(void (*f)(void), unsigned int timeout, bool verbose) {
    pid_t pid = fork();
    if (pid < 0)
        return -1;

    if (pid == 0) {
        // CHILD: Run the function
        f();
        exit(0);  // Just in case f() returns
    }

    // PARENT: Monitor the child
    int status;
    unsigned int elapsed = 0;

    while (1) {
        pid_t result = waitpid(pid, &status, WNOHANG);
        if (result == -1) {
            if (verbose) perror("waitpid");
            return -1;
        } else if (result == 0) {
            // Child still running
            if (elapsed >= timeout) {
                kill(pid, SIGKILL);              // Force kill child
                waitpid(pid, &status, 0);        // Reap zombie
                if (verbose)
                    printf("Bad function: timed out after %u seconds\n", timeout);
                return 0;
            }
            sleep(1);
            elapsed++;
        } else {
            // Child exited or was signaled
            if (WIFEXITED(status)) {
                int code = WEXITSTATUS(status);
                if (code == 0) {
                    if (verbose) printf("Nice function!\n");
                    return 1;
                } else {
                    if (verbose) printf("Bad function: exited with code %d\n", code);
                    return 0;
                }
            } else if (WIFSIGNALED(status)) {
                int sig = WTERMSIG(status);
                if (verbose) printf("Bad function: %s\n", strsignal(sig));
                return 0;
            }
        }
    }

    return -1; // Should not reach
}

// --------------------------------------
// Test functions

void nice_function(void) {
    exit(0);
}

void nonzero_exit_function(void) {
    exit(42);
}

void segfault_function(void) {
    int *p = NULL;
    *p = 123;
}

void abort_function(void) {
    abort();
}

void timeout_function(void) {
    sleep(5);  // Should be killed if timeout < 5
}

void f6(void) {
    printf("-> I will run forever and ignore all signals!\n");
    sigaction(SIGALRM, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGINT,  &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGTERM, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGSEGV, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGPIPE, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGBUS,  &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGCHLD, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGHUP,  &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGTSTP, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGTTIN, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGTTOU, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGURG,  &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    sigaction(SIGQUIT, &(struct sigaction){.sa_handler = SIG_IGN}, NULL);
    while (true) {}
}

// --------------------------------------
// Main to test sandbox

int main(void) {
    printf("Nice Function:\n");
    printf("Return: %d\n\n", sandbox(nice_function, 2, true));

    printf("Non-zero Exit Function:\n");
    printf("Return: %d\n\n", sandbox(nonzero_exit_function, 2, true));

    printf("Segfault Function:\n");
    printf("Return: %d\n\n", sandbox(segfault_function, 2, true));

    printf("Abort Function:\n");
    printf("Return: %d\n\n", sandbox(abort_function, 2, true));

    printf("Timeout Function (sleeps 5s):\n");
    printf("Return: %d\n\n", sandbox(timeout_function, 2, true));

    printf("Evil Function f6 (ignores signals):\n");
    printf("Return: %d\n\n", sandbox(f6, 2, true));

    return 0;
}


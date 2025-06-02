#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose) {
    pid_t pid = fork();
    if (pid < 0)
        return -1;

    if (pid == 0) {
        alarm(timeout);  // Set timeout in child
        f();             // Call test function
        exit(0);         // Exit cleanly if f returns
    }

    int status;
    unsigned int elapsed = 0;

    while (1) {
        pid_t wpid = waitpid(pid, &status, WNOHANG);
        if (wpid == -1)
            return -1;

        if (wpid == pid)
            break;

        sleep(1);
        elapsed++;
        if (elapsed >= timeout) {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);  // Ensure cleanup
            if (verbose)
                printf("Bad function: timed out after %u seconds\n", timeout);
            return 0;
        }
    }

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            if (verbose)
                printf("Nice function!\n");
            return 1;
        } else {
            if (verbose)
                printf("Bad function: exited with code %d\n", code);
            return 0;
        }
    }

    if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        if (verbose)
            printf("Bad function: %s\n", strsignal(sig));
        return 0;
    }

    return -1;
}

// ========== TEST FUNCTIONS ==========

void nice_function(void) {
    // Returns normally
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

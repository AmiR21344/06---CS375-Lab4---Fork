#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("I am the parent, PID: %d\n", getpid());
        wait(NULL);  // Wait for child to finish
    } else if (pid == 0) {
        // Child process
        printf("I am the child, PID: %d\n", getpid());
    } else {
        // Fork failed
        printf("Fork failed!\n");
        return 1;
    }
    return 0;
}
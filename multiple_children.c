#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    
    if (pid1 > 0) {
        // Parent - create second child
        pid_t pid2 = fork();
        
        if (pid2 > 0) {
            // Parent
            printf("I am the parent, PID: %d\n", getpid());
            // Wait for both children
            wait(NULL);
            wait(NULL);
        } else if (pid2 == 0) {
            // Child 2
            printf("Child 2, PID: %d\n", getpid());
        }
        // pid2 < 0 handled below
        
    } else if (pid1 == 0) {
        // Child 1
        printf("Child 1, PID: %d\n", getpid());
    } else {
        // Fork error
        printf("Fork failed!\n");
        return 1;
    }
    
    return 0;
}
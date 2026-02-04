#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();

    if (pid1 > 0) {
        // Parent process
        printf("I am the parent, PID: %d\n", getpid());
        wait(NULL);  // Wait for child (and grandchild) to finish
    } else if (pid1 == 0) {
        // Child process
        printf("I am the child, PID: %d\n", getpid());
        
        pid_t pid2 = fork();  // Create grandchild
        
        if (pid2 > 0) {
            // Still the child process
            wait(NULL);  // Child waits for grandchild
        } else if (pid2 == 0) {
            // Grandchild process
            printf("I am the grandchild, PID: %d\n", getpid());
        } else {
            printf("Second fork failed!\n");
            return 1;
        }
    } else {
        // First fork failed
        printf("First fork failed!\n");
        return 1;
    }
    
    return 0;
}
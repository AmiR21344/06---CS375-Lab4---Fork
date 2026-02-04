#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid1 = fork();
    
    if (pid1 > 0) {
        // Parent - create second child
        pid_t pid2 = fork();
        
        if (pid2 > 0) {
            // Parent process
            printf("I am the parent, PID: %d\n", getpid());
            
            // Wait for both children to finish
            wait(NULL);
            wait(NULL);
            
            printf("Parent process finished.\n");
        } else if (pid2 == 0) {
            // Child 2 - Execute ls command using execlp()
            printf("Child 2 (PID: %d) executing 'ls -l'...\n", getpid());
            
            // execlp replaces the current process with "ls"
            execlp("ls", "ls", "-l", NULL);
            
            // If execlp returns, it means an error occurred
            perror("execlp failed");
            return 1;
        } else {
            // Second fork failed
            printf("Second fork failed!\n");
            return 1;
        }
        
    } else if (pid1 == 0) {
        // Child 1 - regular child process
        printf("Child 1, PID: %d\n", getpid());
    } else {
        // First fork failed
        printf("First fork failed!\n");
        return 1;
    }
    
    return 0;
}
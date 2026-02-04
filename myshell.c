#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 20
#define BUFFER_SIZE 256

int main() {
    char input[BUFFER_SIZE];
    char *args[MAX_ARGS + 1];  // +1 for NULL terminator
    char *token;
    int background;

    while (1) {
        // Print shell prompt
        printf("myshell> ");
        
        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");  // Handle Ctrl+D
            break;
        }
        
        // Remove newline character
        input[strcspn(input, "\n")] = 0;
        
        // Check for empty command
        if (strlen(input) == 0) {
            continue;
        }
        
        // Check for exit command
        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell...\n");
            break;
        }
        
        // Parse command and arguments
        int i = 0;
        token = strtok(input, " ");
        while (token != NULL && i < MAX_ARGS) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        args[i] = NULL;  // NULL terminate for execvp
        
        // Check for background execution (&)
        background = 0;
        if (i > 0 && strcmp(args[i-1], "&") == 0) {
            background = 1;
            args[i-1] = NULL;  // Remove & from arguments
            i--;
        }
        
        // Create child process
        pid_t pid = fork();
        
        if (pid == 0) {
            // Child process
            // Execute command with arguments
            execvp(args[0], args);
            
            // If execvp returns, there was an error
            perror("execvp failed");
            exit(1);
            
        } else if (pid > 0) {
            // Parent process
            if (!background) {
                // Wait for foreground command to complete
                waitpid(pid, NULL, 0);
            } else {
                // Background execution - don't wait
                printf("[%d] Running in background\n", pid);
            }
        } else {
            // Fork failed
            perror("fork failed");
        }
    }
    
    return 0;
}
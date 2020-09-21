#include "process.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_program(char **args) {
    pid_t pid = fork();  
    int status;
  
    if (pid == -1) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == 0) { 
        if (execvp(args[0], args) < 0) { 
            printf("sshell: Could not execute command\n"); 
        } 
        exit(0); 
    } else { 
        // waiting for child to terminate 
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        // wait(NULL);  
        return; 
    } 
} 
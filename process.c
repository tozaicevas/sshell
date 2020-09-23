#include "process.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define FAILED_TO_FORK -1
#define NEWLY_CREATED_CHILD 0

#define READ_FD 0
#define WRITE_FD 1

void wait_for_process_to_end(pid_t pid) {
    int status;
    do {
        waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
};

void execute_program(char **args) {
    pid_t pid = fork();  
  
    if (pid == FAILED_TO_FORK) { 
        printf("\nFailed forking child.."); 
        return; 
    } else if (pid == NEWLY_CREATED_CHILD) { 
        if (execvp(args[0], args) < 0) { 
            printf("sshell: Could not execute command\n"); 
        } 
        exit(0); 
    } else { 
        wait_for_process_to_end(pid);
        return; 
    } 
} 

int spawn_pipe_proc(int in, int out, char **cmd) {
    pid_t pid;

    if ((pid = fork()) == NEWLY_CREATED_CHILD) {
        if (in != STDIN_FILENO) {
            dup2(in, 0);
            close(in);
        }
        if (out != STDOUT_FILENO) {
            dup2(out, 1);
            close(out);
        }

        return execvp(cmd[0], cmd);
    } 

  return pid;
}

void execute_pipes(char *pipes[][1024], int pipes_amount) {
    int i;
    pid_t pid;
    int in, fd[2];

    /* The first process should get its input from stdin */
    in = STDIN_FILENO;

    for (i = 0; i < pipes_amount; i++) {
        pipe(fd);
        spawn_pipe_proc(in, fd[WRITE_FD], pipes[i]);
        close(fd[WRITE_FD]);
        in = fd[READ_FD];
    }

    pid = fork();

    if (pid == NEWLY_CREATED_CHILD) {
        if (in != STDIN_FILENO)
            dup2(in, STDIN_FILENO);
        execvp(pipes[i][0], pipes[i]);
    } else if (pid > 0) {
        wait_for_process_to_end(pid);
    }
}
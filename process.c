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
    wait(NULL);
}

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

int spawn_pipe_proc(int in, int out, char **cmd, int pipe[][2], int proc_index) {
    pid_t pid = fork();

    if (pid == NEWLY_CREATED_CHILD) {
        if (in != STDIN_FILENO) {
            dup2(in, 0);
        }
        if (out != STDOUT_FILENO) {
            dup2(out, 1);
        }

        for (int i=0; i<=proc_index; i++) {
            close(pipe[i][READ_FD]);
            close(pipe[i][WRITE_FD]);
        }

        return execvp(cmd[0], cmd);
    } 

  return pid;
}

void execute_pipes(char *pipes[][1024], int pipes_amount) {
    int in = STDIN_FILENO;
    int processes_amount = pipes_amount + 1;
	int fd[pipes_amount][2];
    int processes[1024] = {0};

    for (int i = 0; i < pipes_amount; i++) {
        pipe(fd[i]);
        processes[i] = spawn_pipe_proc(in, fd[i][WRITE_FD], pipes[i], fd, i);
        in = fd[i][READ_FD];
    }

    processes[pipes_amount] = spawn_pipe_proc(in, STDOUT_FILENO, pipes[pipes_amount], fd, pipes_amount - 1);

    for (int i=0; i<pipes_amount; i++) {
        close(fd[i][WRITE_FD]);
        close(fd[i][READ_FD]);
    }

    for (int i=0; i<processes_amount; i++) {
        wait_for_process_to_end(processes[i]);
    }
}

#ifndef PROCESS_H
#define PROCESS_H

void execute_program(char **args);
void execute_pipes(char *pipes[][1024], int pipes_amount);

#endif

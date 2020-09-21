#ifndef BUILTINS_H
#include <stdbool.h>

#define BUILTINS_H

bool is_builtin(char *input);
void execute_builtin(char **args);

void cd(char **args);
void help(char **args);
void do_exit(char **args);

#endif

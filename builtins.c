#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

void (*builtin_func[]) (char **) = {
  &cd,
  &help,
  &exit
};

int get_builtins_count() {
  return sizeof(builtin_str) / sizeof(char *);
}

bool is_builtin(char *input) {
  for (int i = 0; i < get_builtins_count(); i++) {
    if (strcmp(input, builtin_str[i]) == 0) {
      return true;
    }
  }
  return false;
}

void execute_builtin(char **args) {
  for (int i = 0; i < get_builtins_count(); i++) {
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
}

void cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "sshell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sshell");
    }
  }
}

void help(char **args) {
  printf("sshell (Simple Shell) v0.1\n");
  printf("Builtins: \n");

  for(int i = 0; i < get_builtins_count(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
}

void do_exit(char **args) {
    exit(EXIT_SUCCESS);
}
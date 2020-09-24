#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};

void (*builtin_func[]) (char **) = {
  &cd,
  &help,
  &do_exit
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

void interpolate_home(char *str, char *result) {
  char *after_home = malloc(strlen(str) * sizeof(char));
  strncpy(after_home, str, strlen(str));
  strcat(result, "/home/");
  strcat(result, getenv("USER"));
  strcat(result, after_home);
  free(after_home);
}

void cd(char **args) {
  bool includes_home = false;
  char arg_with_home_path[1024] = {0};

  if (args[1][0] == '~') {
   includes_home = true; 
   interpolate_home(args[1] + 1, arg_with_home_path);
  }

  if (args[1] == NULL) {
    fprintf(stderr, "sshell: expected argument to \"cd\"\n");
  } else {
    if (chdir(includes_home ? arg_with_home_path : args[1]) != 0) {
      perror("sshell: cd");
    }
  }
}

void help(char **args) {
  printf("sshell (Simple Shell) v0.1\n");
  printf("Builtins: \n");

  for (int i = 0; i < get_builtins_count(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
}

void do_exit(char **args) {
    exit(EXIT_SUCCESS);
}
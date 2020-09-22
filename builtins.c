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
  // bool includes_home = false;
  // char arg_with_home_path[1024] = {0};
  // char *after_home;
  // if (args[1][0] == '~') {
  //  includes_home = true; 
  //  after_home = malloc((strlen(args[1]) - 1) * sizeof(char));
  //  strncpy(after_home, args[1]+1, strlen(args[1]) - 1);
  //  strcat(arg_with_home_path, "/home/");
  //  strcat(arg_with_home_path, getenv("USER"));
  //  strcat(arg_with_home_path, after_home);
  // }
  if (args[1] == NULL) {
    fprintf(stderr, "sshell: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("sshell: cd");
    }
    // if (chdir(includes_home ? arg_with_home_path : args[1]) != 0) {
    //   perror("sshell: cd");
    // }
    // free(after_home);
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
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
  printf("sshell (Simple Shell)\n");
  printf("Builtins: \n");

  for(int i = 0; i < get_builtins_count(); i++) {
    printf("  %s\n", builtin_str[i]);
  }
}

void do_exit(char **args) {
    exit(EXIT_SUCCESS);
}
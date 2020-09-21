#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char *get_current_dir(void) { 
    char *cwd = (char *) malloc(1024);
    getcwd(cwd, sizeof(1024)); 
    return cwd;
} 

void print_prompt(void) {
  char *current_dir = get_current_dir();
  char *user_name = getenv("USER");

  printf("[%s %s]$ ", user_name, strcmp(current_dir, "") == 0 ? "~" : current_dir);
  free(current_dir);
}

char *read_input(void) {
  const int BUF_SIZE = 1024;
  int position = 0;
  char *buffer = (char *) malloc(sizeof(char) * BUF_SIZE);
  int input;

  if (!buffer) {
    fprintf(stderr, "Allocation error, exiting\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    input = getchar();
    if (input == -1) {
      fprintf(stderr, "EOT\n");
      exit(EXIT_FAILURE);
    }

    if (input == EOF || input == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = input;
    }

    position++;
  }
}
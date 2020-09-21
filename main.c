#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int hey() {
  return 5;
}

void stdin_loop(void) {
  char *line;
  char **args;
  int status;
    
  do {
    print_prompt();

    char *input = read_input();
    process_input(input);
    // line = lsh_read_line();
    // args = lsh_split_line(line);
    // status = lsh_execute(args);

    free(input);

    // free(line);
    // free(args);
  } while (1);
}

int main(int argc, char **argv) {
  stdin_loop();

  return EXIT_SUCCESS;
}

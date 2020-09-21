#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parser.h"

void stdin_loop(void) {
  char *parsed_args[1024]; 
  char* parsed_args_piped[1024]; 
    
  do {
    print_prompt();

    char *input = read_input();
    process_input(input);
    // line = lsh_read_line();
    // args = lsh_split_line(line);
    // status = lsh_execute(args);

    free(input);
  } while (1);
}

int main(int argc, char **argv) {
  stdin_loop();

  return EXIT_SUCCESS;
}

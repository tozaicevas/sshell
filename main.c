#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "parser.h"

#define clear() printf("\033[H\033[J") 

void stdin_loop(void) {
  do {
    print_prompt();

    char *input = read_input();
    process_input(input);

    free(input);
  } while (1);
}

int main(int argc, char **argv) {
  stdin_loop();

  return EXIT_SUCCESS;
}

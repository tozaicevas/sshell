#include "parser.h"
#include "builtins.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **parse_space(char *str, char **parsed) { 
    for (int i = 0; i < 1024; i++) { 
        parsed[i] = strsep(&str, " "); 
        bool is_last_char_newline = parsed[i] != NULL && strlen(parsed[i]) > 1 && parsed[i][strlen(parsed[i]) - 1] == '\n';
        if (is_last_char_newline) {
            parsed[i][strlen(parsed[i]) - 1] = 0;
        }
        printf("[DEBUG] parsed[%d]: %s\n", i, parsed[i]);
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 

    return parsed;
} 

void process_input(char *input) {
    char *parsed[1024];
//   char *parsed_args_piped[1024]; 

  char **parsed_args = parse_space(input, parsed);
  if (is_builtin(parsed_args[0])) {
      execute_builtin(parsed_args);
  } else {
      execute_program(parsed_args);
  }
}
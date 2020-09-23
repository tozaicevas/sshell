#include "parser.h"
#include "builtins.h"
#include "process.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **parse_words(char *str, char **parsed) { 
    for (int i = 0; i < 1024; i++) { 
        parsed[i] = strsep(&str, " "); 
        bool is_last_char_newline = parsed[i] != NULL && strlen(parsed[i]) > 1 && parsed[i][strlen(parsed[i]) - 1] == '\n';

        if (is_last_char_newline) {
            parsed[i][strlen(parsed[i]) - 1] = 0;
        }
        // printf("[DEBUG] parsed[%d]: %s\n", i, parsed[i]);
  
        if (parsed[i] == NULL) 
            break; 
        if (strlen(parsed[i]) == 0) 
            i--; 
    } 

    return parsed;
} 

int get_pipes_amount(char *input, char **pipes) {
    int amount = 0;
    for (int i = 0; i < 1024; i++) { 
        // FIXME: check if | is not inside quotes
        pipes[i] = strsep(&input, "|"); 
        // printf("pipes[%d]: %s\n", i, pipes[i]);
        if (pipes[i] == NULL) 
            break; 
        else
            amount++;
    } 

    return amount - 1;
}

void process_input(char *input) {
    int pipes_amount = false;
    char *parsed[1024];
    char *pipes[1024];

    pipes_amount = get_pipes_amount(input, pipes);

    if (pipes_amount >= 1) {
        char *parsed_pipes[pipes_amount + 1][1024];
        for (int i=0; i<pipes_amount + 1; i++) {
            parse_words(pipes[i], parsed_pipes[i]);
        }
        execute_pipes(parsed_pipes, pipes_amount);
    } else {
        char **parsed_args = parse_words(input, parsed);
        if (is_builtin(parsed_args[0])) {
            execute_builtin(parsed_args);
        } else {
            execute_program(parsed_args);
        }
    }

}
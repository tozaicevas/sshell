#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define RESET   "\033[0m"
#define BLUE    "\033[34m"

void print_current_dir(void) { 
    char full_path[1024]; 
    char *user_name = getenv("USER");
    getcwd(full_path, sizeof(full_path)); 

    char home_path[2048] = {0};
    strcat(home_path, "/home/"); 
    strcat(home_path, user_name); 

    char *dir = strcmp(full_path, home_path) == 0 ? (char *) "~" : full_path;
    printf(BLUE "%s" RESET, dir); 
} 

void print_prompt(void) {
    char *user_name = getenv("USER");
    char host_name[1024];
    gethostname(host_name, 1024);
    
    printf("[%s@%s ", user_name, host_name);
    print_current_dir();
    printf("]$ ");
}

char *read_input(void) {
  char *line = NULL;
  size_t bufsize = 0; 

  if (getline(&line, &bufsize, stdin) == -1) {
    if (feof(stdin)) {
      exit(EXIT_SUCCESS);  
    } else  {
      perror("readline");
      exit(EXIT_FAILURE);
    }
  }

  return line;
}
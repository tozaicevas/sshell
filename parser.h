#ifndef PARSER_H
#define PARSER_H

typedef enum INPUT_STATUS { BUILTIN, PROGRAM, PIPE } INPUT_STATUS;

void process_input(char *input);

#endif

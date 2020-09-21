#ifndef PARSER_H
#define PARSER_H

typedef enum INPUT_STATUS { BUILTIN, PROGRAM, PIPE } INPUT_STATUS;

INPUT_STATUS process_input(char *input);

#endif

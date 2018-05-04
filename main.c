#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libzephir.h"

int main(int argc, char* argv[])
{
  FILE *fp;
  char ch;
  const char *result;
  char *program;
  int i, length;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s /path/to/the/file.zep\n", argv[0]);
    return 1;
  }

  fp = fopen(argv[1], "r");
  if (!fp) {
    fprintf(stderr, "Cant open file\n");
    return 1;
  }

  length = 1024;
  program = malloc(sizeof(char) * length);

  i =0;
  while (!feof(fp)) {
    ch = fgetc(fp);
    if (i == length) {
      length += 1024;
      program = realloc(program, sizeof(char) * length);
    }
    program[i++] = ch;
  }

  program[i - 1] = '\0';
  fclose(fp);

  int retval;
  retval = parse_program(&result, program, i - 1, argv[1]);

  free(program);

  fprintf(stdout, "Status: %d\n", retval); 
  fprintf(stdout, "Result:\n%s\n", result); 
  fprintf(stdout, "Done\n");

  return 0;
}

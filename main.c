#include <stdio.h>

struct data_t {};

void print_help() {
  printf("Here is the help manual: \n"
         "-c <todo_name> | create a todo\n"
         "-l | list all todos\n"
         "-d | delete a particular todo\n");
}
int main(int argc, char *argv[]) {
  printf("Hello world \n");

  printf("Received %d arguments\n", argc);

  if (argc < 1) {
    print_help();
  }

  for (int i = 0; i < argc; i++) {
    printf("Argument: %s\n", argv[i]);
  }

  int read = 0;
  char **moving_ptr = argv;
  while (read < argc) { // 0 < 2, 0 < 1
    printf("Argument (ptr loop method): %s\n", *moving_ptr);
    moving_ptr = moving_ptr + 1;
    read++;
  }
}

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

struct data_t {};

void print_help() {
  printf("Here is the help manual: \n"
         "-c <todo_name> | create a todo\n"
         "-l | list all todos\n");
}

// TODO: use global finalize function for sqlite handle
int main(int argc, char *argv[]) {
  printf("Hello world \n");

  sqlite3 *handle;
  int result = sqlite3_open("data.db", &handle);
  if (result != SQLITE_OK) {
    fprintf(stderr, "problem in opening database");
    return -1;
  }

  sqlite3_stmt *statement;
  result = sqlite3_prepare(
      handle, "CREATE TABLE IF NOT EXISTS todos (name TEXT NOT NULL);", 1000,
      &statement, NULL);
  if (result != SQLITE_OK) {
    fprintf(stderr, "problem in preparing sql statement");
    return -1;
  }

  printf("Successfully prepared statement\n");

  result = sqlite3_step(statement);
  if (result != SQLITE_DONE) {
    fprintf(stderr, "problem in step function");
    return -1;
  }

  sqlite3_finalize(statement);

  printf("Received %d arguments\n", argc);
  for (int i = 0; i < argc; i++) {
    printf("Argument: %s\n", argv[i]);
  }

  if (argc <= 1) {
    print_help();
  }

  char *first_arg = argv[1];
  if (strcmp(first_arg, "-c") == 0) {
    printf("Printing argument: %s", first_arg);

    result = sqlite3_prepare(handle, "INSERT INTO todos (name) VALUES (?);", -1,
                             &statement, NULL);
    if (result != SQLITE_OK) {
      fprintf(stderr, "problem in preparing insert statement");
      return -1;
    }

    sqlite3_bind_text(statement, 1, argv[2], -1, SQLITE_STATIC);

    result = sqlite3_step(statement);
    if (result != SQLITE_DONE) {
      fprintf(stderr, "problem in executing insert statement: %d", result);
      return -1;
    }

    sqlite3_finalize(statement);
  } else if (strcmp(first_arg, "-l") == 0) {
    result = sqlite3_prepare(handle, "SELECT name FROM todos;", -1, &statement,
                             NULL);
    while ((result = sqlite3_step(statement)) == SQLITE_ROW) {
      const char *name = (const char *)sqlite3_column_text(statement, 0);
      printf("Todo: %s\n", name);
    }
    if (result != SQLITE_DONE) {
      fprintf(stderr, "problem in executing select statement: %d", result);
      return -1;
    }

    sqlite3_finalize(statement);
  }

  sqlite3_close(handle);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute(char *input, int status) {
  if (system(input) == 0) {
    if (strcmp(input, "exit")) {
      status = 0;
    }
  }
  else {
    puts("oops..");
  }
}

void readline() {
  int bufsize = 1024;
  char *buffer = malloc(sizeof(char) * bufsize);
}

void run() {
  int status = 1;

  do {
    printf("> ");
    readline();
    execute();
  } while (status);
}

int main() {
  run();
}

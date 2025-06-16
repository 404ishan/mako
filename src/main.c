#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define BUFSIZE 1024
#define TOKBUFSIZE 64
#define TOKDEL " \t\r\n\a"

char *readline() {
  int bufsize = BUFSIZE;
  char *buffer = malloc(sizeof(char) * bufsize);

  if (!buffer) {
    fprintf(stderr, "oops");
  }

  int index = 0;
  int c;
  
  while(1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[index] = '\0';
      return buffer;
    }
    else {
      buffer[index] = c;
    }
    index++;

    if (index >= bufsize) {
      bufsize += BUFSIZE;
      buffer = realloc(buffer, sizeof(char) * bufsize);

      if (!buffer) {
        puts("oops");
      }
    }
  }
}

char **parseline(char *input) {
  int bufsize = TOKBUFSIZE;
  int index = 0;
  char **tokens = malloc(sizeof(char*) * bufsize);

  if (!tokens) {
    fprintf(stderr, "oops");
  }

  char *token;
  token = strtok(input, TOKDEL);

  while (token != NULL) {
    tokens[index] = token;
    index++;

    if (index >= bufsize) {
      bufsize += TOKBUFSIZE;
      tokens = realloc(tokens, sizeof(char*) * bufsize);

      if (!tokens) {
        fprintf(stderr, "oops");
      }
    }

    token = strtok(NULL, TOKDEL);
  }

  tokens[index] = NULL;
  return tokens;
}

int execute(char **args) {
  int status;

  pid_t pid = fork();
  pid_t wpid;

  if (strcmp(args[0], "exit") == 0) {
    return 0;
  }

  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("oops..");
    }
    exit(EXIT_FAILURE);
  }

  else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

void run() {
  int status;

  do {
    printf("> ");
    char *input = readline();
    char **args = parseline(input);
    status = execute(args);

    free(input);
    free(args);
  } while (status);
}

void main() {
  run();
}

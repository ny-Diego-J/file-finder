#include "getdirs.h"
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *getInput(char input[64]) {
  scanf("%63[^\n]", input);
  return input;
}

void appendChar(char *dest, char *src, size_t dest_capacity) {

  size_t dest_len = strlen(dest);

  // We subtract dest_len and 1 (for the null terminator '\0')
  size_t remaining_space = dest_capacity - dest_len - 1;

  // 3. Safe append
  strncat(dest, src, remaining_space);
}

void *startRead(void *args) {
  readDirs(".", 0);
  return NULL;
}

void multithread() {

  pthread_t thread;
  pthread_create(&thread, NULL, startRead, NULL);
  pthread_join(thread, NULL);

  printf("Main thread finished.\n");
}

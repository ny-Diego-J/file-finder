#include "getdirs.h"
#include "ui.h"
#include <dirent.h>
#include <fcntl.h>
#include <linux/limits.h>
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
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  readDirs(cwd, 0, args);
  return NULL;
}
void *startui(void *args) {
  drawui(args);
  return NULL;
}

void multithread(FileList *list) {

  pthread_t searchthread;
  pthread_t uithread;
  pthread_create(&searchthread, NULL, startRead, list);
  pthread_create(&uithread, NULL, startui, list);
  pthread_join(searchthread, NULL);
  pthread_join(uithread, NULL);

  printf("Main thread finished.\n");
}

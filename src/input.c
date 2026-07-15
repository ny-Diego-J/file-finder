#include "file_item.h"
#include "getdirs.h"
#include "ui.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void append_char(char *dest, char *src, size_t dest_capacity) {

  size_t dest_len = strlen(dest);

  // We subtract dest_len and 1 (for the null terminator '\0')
  size_t remaining_space = dest_capacity - dest_len - 1;

  // 3. Safe append
  strncat(dest, src, remaining_space);
}

void *start_read(void *args) {
  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  read_dirs(cwd, 0, args);
  return NULL;
}
void *star_tui(void *args) {
  drawui(args);
  return NULL;
}

void multithread(file_list *list) {

  pthread_t searchthread;
  pthread_t uithread;
  pthread_create(&searchthread, NULL, start_read, list);
  pthread_create(&uithread, NULL, star_tui, list);
  pthread_join(searchthread, NULL);
  pthread_join(uithread, NULL);

  printf("Main thread finished.\n");
}

#include "input.h"
#include "dir_queue.h"
#include "file_item.h"
#include "getdirs.h"
#include "ui.h"
#include <dirent.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void append_char(char *dest, char *src, size_t dest_capacity) {

  size_t dest_len = strlen(dest);

  size_t remaining_space = dest_capacity - dest_len - 1;

  strncat(dest, src, remaining_space);
}

void *start_tui(void *args) {
  drawui(args);
  return NULL;
}

/**
 * make multiple threads.
 * First thread takes every directory and adds it to the queue
 * the others wait and as soon they get one available folder the tkae it and
 */
void init_threads(file_list *list, int amount, char *path, bool is_all,
                  bool is_relative_path) {
  char cwd[PATH_MAX];
  if (path == NULL) {
    getcwd(cwd, sizeof(cwd));
  } else {
    // TODO: implement for absolute and relatvie path
  }

  dir_queue queue;
  init_queue(&queue, list);

  pthread_t search_threads[amount];

  pthread_t uithread;
  enqueue(&queue, cwd);

  ui_flags flags;
  flags.is_relative_path = is_relative_path;
  flags.list = list;
  strcpy(flags.path, cwd);

  pthread_create(&uithread, NULL, start_tui, &flags);

  for (int i = 0; i < amount; i++) {
    pthread_create(&search_threads[i], NULL, search_worker, &queue);
  }

  for (int i = 0; i < amount; i++) {
    pthread_join(search_threads[i], NULL);
  }
  pthread_join(uithread, NULL);

  destroy_queue(&queue);
}

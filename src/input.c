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
char ignore_paths[][10] = {".", "..", ".git", ".cache", ".local", ".cargo"};
char ignore_minimum[][10] = {".", ".."};
int length = sizeof(ignore_paths) / sizeof(ignore_paths[0]);
int minimum_lenght = sizeof(ignore_minimum) / sizeof(ignore_minimum[0]);

bool search_all_files;

/**
 * @brief Checks if the directory should be ignored.
 *
 * @param name The directory name to compare to the ignore list.
 * @return 1 if it matches the ignore list, 0 otherwise.
 */
int is_valid_directory(char *name) {
  if (search_all_files) {
    for (int i = 0; i < minimum_lenght; i++) {
      if (!strcmp(name, ignore_minimum[i])) {
        return 0;
      }
    }
  } else {
    for (int i = 0; i < length; i++) {
      if (!strcmp(name, ignore_paths[i])) {
        return 0;
      }
    }
  }
  return 1;
}

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
 * Makes multiple threads.
 * First thread takes every directory and adds it to the queue
 * the others wait and as soon they get one available folder the tkae it and
 */
void init_threads(file_list *list, int amount, char *path, bool is_all,
                  bool is_relative_path, enum output output) {
  search_all_files = is_all;

  char cwd[PATH_MAX];
  if (path == NULL) {
    getcwd(cwd, sizeof(cwd));
  } else {
    if (path[0] == '/') {
      strcpy(cwd, path);
    } else {
      getcwd(cwd, sizeof(cwd));
      append_char(cwd, "/", sizeof(cwd));
      append_char(cwd, path, sizeof(cwd));
    }
  }

  dir_queue queue;
  init_queue(&queue, list);

  pthread_t search_threads[amount];

  pthread_t uithread;
  enqueue(&queue, cwd);

  ui_flags flags;
  flags.is_relative_path = is_relative_path;
  flags.list = list;
  flags.output = output;
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
  clear_list(list);
}

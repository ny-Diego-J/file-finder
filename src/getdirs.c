#include "dir_queue.h"
#include "input.h"
#include <dirent.h>
#include <string.h>
#define MAX_LENGHT 20
char ignore_paths[][MAX_LENGHT] = {".", "..", ".git", ".cache"};
int length = sizeof(ignore_paths) / sizeof(ignore_paths[0]);

/**
 * @brief Checks if the directory should be ignored.
 *
 * @param name The directory name to compare to the ignore list.
 * @return 1 if it matches the ignore list, 0 otherwise.
 */
int is_valid_directory(char *name) {
  for (int i = 0; i < length; i++) {
    if (!strcmp(name, ignore_paths[i])) {
      return 0;
    }
  }
  return 1;
}

/**
 * reads the given directory. Adds the found files to the list and the directory
 * to the queue
 * @param path to check
 * @param queue to add to
 */
void read_dirs(char *path, dir_queue *queue) {

  DIR *dir = opendir(path);
  if (dir == NULL) {
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      add_file(queue->list, entry->d_name, path);
    }

    if (entry->d_type == DT_DIR) {
      if (is_valid_directory(entry->d_name)) {
        char full_path[1024] = "";

        append_char(full_path, path, sizeof(full_path));

        if (strcmp(path, "/")) {
          append_char(full_path, "/", sizeof(full_path));
        }

        append_char(full_path, entry->d_name, sizeof(full_path));

        enqueue(queue, full_path);
      }
    }
  }
  closedir(dir);
}

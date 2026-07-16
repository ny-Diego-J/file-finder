#include "dir_queue.h"
#include "file_item.h"
#include "input.h"
#include <dirent.h>
#include <string.h>

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
      if (strcmp(entry->d_name, ".") != 0 &&
          strcmp(entry->d_name, ".cache") != 0 &&
          strcmp(entry->d_name, "..") != 0) {
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

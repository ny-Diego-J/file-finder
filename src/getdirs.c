#include "dir_queue.h"
#include "file_item.h"
#include "input.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>

void read_dirs(char *path, dir_queue *queue) {

  DIR *dir = opendir(path);
  if (dir == NULL) {
    if (errno == EACCES) {
      // fprintf(stderr, "Permission denied: Cannot access directory
      // '%s'\n",path);
    } else {
      // Handles other errors like ENOENT (Directory does not exist)
      // fprintf(stderr, "Error opening '%s': %s\n", path, strerror(errno));
    }
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      add_file(queue->list, entry->d_name, path);
    }
    if (entry->d_type == DT_DIR) {
      // if (!strstr(entry->d_name, ".")) {
      char full_path[1024] = "";

      append_char(full_path, path, sizeof(full_path));

      if (strcmp(path, "/")) {
        append_char(full_path, "/", sizeof(full_path));
      }

      append_char(full_path, entry->d_name, sizeof(full_path));

      enqueue(queue, full_path);
      //}
    }
  }
  closedir(dir);
}

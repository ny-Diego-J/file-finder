#include "file_item.h"
#include "input.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void readDirs(char *path, int padding, file_list *list) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    perror("unable to open dir");
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      add_file(list, entry->d_name, path);
    }
    if (entry->d_type == DT_DIR) {
      if (!strstr(entry->d_name, ".")) {
        char full_path[1024] = "";
        appendChar(full_path, path, sizeof(full_path));

        appendChar(full_path, "/", sizeof(full_path));
        appendChar(full_path, entry->d_name, sizeof(full_path));
        readDirs(full_path, padding + 2, list);
      }
    }
  }
  closedir(dir);
}

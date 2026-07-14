#include "FileItem.h"
#include "input.h"
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void readDirs(char *path, int padding, FileList *list) {
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
      if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".") &&
          strcmp(entry->d_name, ".git") && strcmp(entry->d_name, ".local")) {
        char full_path[1024] = "";
        appendChar(full_path, path, sizeof(full_path));

        appendChar(full_path, "/", sizeof(full_path));
        appendChar(full_path, entry->d_name, sizeof(full_path));
        readDirs(full_path, padding + 2, list);
      } else {
        // printf("dir %s doe not match\n", entry->d_name);
      }
    }
  }
  closedir(dir);
}

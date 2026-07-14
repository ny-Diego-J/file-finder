#include "input.h"
#include <dirent.h>
#include <fcntl.h>
#include <pthread.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void readDirs(char path[64], int padding) {
  DIR *dir = opendir(path);
  if (dir == NULL) {
    perror("unable to open dir");
    return;
  }

  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      for (int i = 0; i < padding; i++) {
        printf(" ");
      }
      printf("file %s\n", entry->d_name);
    }
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".") &&
          strcmp(entry->d_name, ".git")) {
        for (int i = 0; i < padding; i++) {
          printf(" ");
        }
        printf("dir %s\n", entry->d_name);
        char full_path[128] = "";

        appendChar(full_path, path, sizeof(full_path));

        appendChar(full_path, "/", sizeof(full_path));
        appendChar(full_path, entry->d_name, sizeof(full_path));
        readDirs(full_path, padding + 2);
      } else {
        // printf("dir %s doe not match\n", entry->d_name);
      }
    }
  }
}

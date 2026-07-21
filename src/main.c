#include "file_item.h"
#include "input.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool is_matching_flag(char *flag, int count, ...) {
  va_list args;
  va_start(args, count);
  bool found = false;

  for (int i = 0; i < count; i++) {
    char *match = va_arg(args, char *);
    if (!strcmp(flag, match)) {
      found = true;
      break;
    }
  }
  va_end(args);
  return found;
}

int main(int argc, char *argv[]) {
  int num;
  num = sysconf(_SC_NPROCESSORS_ONLN) * 2;
  bool is_all = false;
  bool is_relative_path = false;
  enum output output = STDOUT;
  char *path = NULL;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (is_matching_flag(argv[i], 2, "-a", "--all")) {
        is_all = true;
      } else if (is_matching_flag(argv[i], 2, "-t", "--threads")) {
        if (i + 1 < argc) {
          num = atoi(argv[i + 1]);
          i++;
        } else {
          printf("Please enter a thread amount");
          exit(1);
        }
      } else if (is_matching_flag(argv[i], 2, "-r", "--relative")) {
        is_relative_path = true;
      } else if (is_matching_flag(argv[i], 2, "-e", "--editor")) {
        output = EDITOR;
      } else if (is_matching_flag(argv[i], 2, "-c", "--clipboard")) {
        output = CLIPBOARD;
      } else {
        printf("%s is not a valid flag. Exiting\n", argv[i]);
        exit(1);
      }
    } else {
      path = argv[i];
    }
  }

  file_list list;
  create_List(&list);
  init_threads(&list, num, path, is_all, is_relative_path, output);
  return 0;
}

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
      } else if (is_matching_flag(argv[i], 2, "-h", "--help")) {
        printf(
            "Usage: fif [OPTIONS] [SEARCH_DIRECTORY]\n"
            "\n"
            "A fast, multithreaded file searching utility with an interactive "
            "ncurses interface.\n"
            "\n"
            "DESCRIPTION:\n"
            "    Searches the filesystem for the search querry.\n"
            "\n"
            "ARGUMENTS:\n"
            "    [SEARCH_DIRECTORY]         Starting search directory.\n"
            "                               Uses the current directory if no "
            "other is given.\n"
            "\n"
            "OPTIONS:\n"
            "    -h, --help                 Show this help message and exit.\n"
            "    -a, --all                  Includes directories like .git or "
            ".cache.\n"
            "    -t, --threads [amount]     Set the amount of search threads.\n"
            "    -r, --relative             Displays the realtive file path "
            "instead of the absolute.\n"
            "    -e, --editor               Opens the file in the $EDITOR.\n"
            "    -c, --clipboard            Copys the path to the clipboard. "
            "Needs xclip.\n"
            "\n"
            "\n"
            "EXAMPLES:\n"
            "    fyf dev\n"
            "    fyf -a\n");
        exit(0);
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

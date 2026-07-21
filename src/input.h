#include "file_item.h"
#include <linux/limits.h>
#include <stdbool.h>
#include <stddef.h>
#ifndef INPUT
#define INPUT
typedef struct {
  file_list *list;
  bool is_relative_path;
  char path[PATH_MAX];
} ui_flags;

int is_valid_directory(char *name);
void init_threads(file_list *list, int amount, char *path, bool is_all,
                  bool is_relative_path);
void append_char(char *dest, char *src, size_t dest_capacity);
#else
#endif // !INPUT

#include "file_item.h"
#include <stdlib.h>
#include <string.h>

void create_List(file_list *list) {
  list->count = 0;
  list->capacity = 8;
  list->items = malloc(list->capacity * sizeof(file_item));
  pthread_mutex_init(&list->lock, NULL);
}

void add_file(file_list *list, const char *name, const char *path) {
  pthread_mutex_lock(&list->lock);
  if (list->count >= list->capacity) {
    list->items =
        realloc(list->items, (list->capacity * 2) * sizeof(file_item));
    list->capacity = list->capacity * 2;
  }
  file_item new_item;
  strcpy(new_item.name, name);
  strcpy(new_item.path, path);
  list->items[list->count] = new_item;
  list->count = list->count + 1;
  pthread_mutex_unlock(&list->lock);
}

void clear_list(file_list *list) {
  list->count = 0;
  list->capacity = 8;
  free(list->items);
  list->items = NULL;
}

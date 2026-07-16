#include "file_item.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>

void create_List(file_list *list) {
  list->count = 0;
  list->capacity = 8;
  list->items = malloc(list->capacity * sizeof(file_item));

  pthread_mutex_init(&list->lock, NULL);
}

void create_filtered_List(filtered_file_list *list) {
  list->count = 0;
  list->capacity = 8;
  list->items = malloc(list->capacity * sizeof(file_item *));
}

void add_file(file_list *list, const char *name, const char *path) {
  pthread_mutex_lock(&list->lock);
  if (list->count >= list->capacity) {
    list->items =
        realloc(list->items, (list->capacity * 2) * sizeof(file_item));
    list->capacity = list->capacity * 2;
  }
  file_item new_item;

  new_item.name = strdup(name);
  new_item.path = strdup(path);
  new_item.score = 0.0;

  list->items[list->count] = new_item;
  list->count = list->count + 1;
  pthread_mutex_unlock(&list->lock);
}

void add_file_to_filtered_list(filtered_file_list *list, file_item *file) {
  if (list->count >= list->capacity) {
    list->capacity = list->capacity * 2;
    list->items = realloc(list->items, list->capacity * sizeof(file_item *));
  }

  list->items[list->count] = file;
  list->count = list->count + 1;
}

void clear_list(file_list *list) {
  pthread_mutex_lock(&list->lock);
  for (int i = 0; i < list->count; i++) {
    free(list->items[i].name);
    free(list->items[i].path);
  }

  free(list->items);
  list->items = NULL;
  list->count = 0;
  list->capacity = 0;
  pthread_mutex_unlock(&list->lock);
  pthread_mutex_destroy(&list->lock);
}

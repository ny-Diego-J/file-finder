#include "FileItem.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void create_List(FileList *list) {
  list->count = 0;
  list->capacity = 8;
  list->items = malloc(list->capacity * sizeof(FileItem));
  pthread_mutex_init(&list->lock, NULL);
}

void add_file(FileList *list, const char *name, const char *path) {
  pthread_mutex_lock(&list->lock);
  if (list->count >= list->capacity) {
    list->items = realloc(list->items, (list->capacity * 2) * sizeof(FileItem));
    list->capacity = list->capacity * 2;
  }
  FileItem newItem;
  strcpy(newItem.name, name);
  strcpy(newItem.path, path);
  list->items[list->count] = newItem;
  list->count = list->count + 1;
  pthread_mutex_unlock(&list->lock);
}

void clear_list(FileList *list) {
  list->count = 0;
  list->capacity = 8;
  free(list->items);
  list->items = NULL;
}

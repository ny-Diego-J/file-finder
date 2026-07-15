#pragma once
#include <pthread.h>
#ifndef FILE_ITEM
#define FILE_ITEM
typedef struct {
  char name[265];
  char path[2048];
  int score;
} file_item;

typedef struct {
  file_item *items;
  int count;
  int capacity;
  pthread_mutex_t lock;
} file_list;

void create_List(file_list *list);

void add_file(file_list *list, const char *name, const char *path);
void add_file_to_list(file_list *list, file_item file);

#endif // !FILE_ITEM

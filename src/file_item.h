#pragma once
#include <pthread.h>
#ifndef FILE_ITEM
#define FILE_ITEM
typedef struct {
  char *name;
  char *path;
  int score;
} file_item;

typedef struct {
  file_item *items;
  int count;
  int capacity;
  pthread_mutex_t lock;
} file_list;
typedef struct {
  file_item **items;
  int count;
  int capacity;
  pthread_mutex_t lock;
} filtered_file_list;

void create_List(file_list *list);
void create_filtered_List(filtered_file_list *list);

void add_file(file_list *list, const char *name, const char *path);
void add_file_to_filtered_list(filtered_file_list *list, file_item *file);

#endif // !FILE_ITEM

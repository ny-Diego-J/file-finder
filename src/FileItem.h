#pragma once
#include <pthread.h>
#ifndef FILE_ITEM
#define FILE_ITEM
typedef struct {
  char name[265];
  char path[2048];
} FileItem;

typedef struct {
  FileItem *items;
  int count;
  int capacity;
  pthread_mutex_t lock;
} FileList;

void create_List(FileList *list);

void add_file(FileList *list, const char *name, const char *path);

#endif // !FILE_ITEM

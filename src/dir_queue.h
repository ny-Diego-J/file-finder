#include "file_item.h"
#include <pthread.h>
#ifndef DIR_QUEUE_H
#define DIR_QUEUE_H
typedef struct {
  char **paths;
  int head;
  int tail;
  int count;
  int capacity;
  int active_threads;
  file_list *list;
  pthread_mutex_t lock;
  pthread_cond_t cond;
} dir_queue;

void destroy_queue(dir_queue *queue);
void init_queue(dir_queue *queue, file_list *list);
void enqueue(dir_queue *queue, char *path);
char *dequeue(dir_queue *queue);

void *search_worker(void *arg);
void finish_work(dir_queue *queue);
#endif // DIR_QUEUE_H

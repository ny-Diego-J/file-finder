#include "dir_queue.h"
#include "file_item.h"
#include "getdirs.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void init_queue(dir_queue *queue, file_list *list) {
  queue->capacity = 50000;
  queue->count = 0;
  queue->head = 0;
  queue->tail = 0;
  queue->active_threads = 0;
  queue->list = list;
  queue->paths = malloc(queue->capacity * sizeof(char *));

  pthread_mutex_init(&queue->lock, NULL);
  pthread_cond_init(&queue->cond, NULL);
}

// add to queue
void enqueue(dir_queue *queue, char *path) {
  pthread_mutex_lock(&queue->lock);

  if (queue->count >= queue->capacity) {
    int new_capacity = queue->capacity * 2;
    char **new_paths = malloc(new_capacity * sizeof(char *));

    if (new_paths != NULL) {
      for (int i = 0; i < queue->count; i++) {
        new_paths[i] = queue->paths[(queue->head + i) % queue->capacity];
      }
      free(queue->paths);
      queue->paths = new_paths;
      queue->head = 0;
      queue->tail = queue->count;
      queue->capacity = new_capacity;
    } else {
      pthread_mutex_unlock(&queue->lock);
      return;
    }
  }

  queue->paths[queue->tail] = strdup(path);
  queue->tail = (queue->tail + 1) % queue->capacity;
  queue->count += 1;

  pthread_cond_signal(&queue->cond);
  pthread_mutex_unlock(&queue->lock);
}

// remove from queue
char *dequeue(dir_queue *queue) {
  pthread_mutex_lock(&queue->lock);

  while (queue->count == 0 && queue->active_threads > 0) {
    pthread_cond_wait(&queue->cond, &queue->lock);
  }
  if (queue->count == 0 && queue->active_threads == 0) {
    pthread_mutex_unlock(&queue->lock);
    return NULL;
  }

  char *path = queue->paths[queue->head];
  queue->head = (queue->head + 1) % queue->capacity;
  queue->count -= 1;

  queue->active_threads += 1;
  pthread_mutex_unlock(&queue->lock);
  return path;
}

void *search_worker(void *arg) {
  dir_queue *queue = (dir_queue *)arg;

  while (1) {
    char *path = dequeue(queue);
    if (path == NULL) {
      break;
    }

    read_dirs(path, queue);

    free(path);
    finish_work(queue);
  }
  return NULL;
}

void finish_work(dir_queue *queue) {
  pthread_mutex_lock(&queue->lock);
  queue->active_threads -= 1;

  if (queue->count == 0 && queue->active_threads == 0) {
    pthread_cond_broadcast(&queue->cond);
  }
  pthread_mutex_unlock(&queue->lock);
}

void destroy_queue(dir_queue *queue) {
  free(queue->paths);
  pthread_mutex_destroy(&queue->lock);
  pthread_cond_destroy(&queue->cond);
}

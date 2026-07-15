#include "file_item.h"
#include <ctype.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int compare_function(const void *a, const void *b) {
  const file_item *itemA = (const file_item *)a;
  const file_item *itemB = (const file_item *)b;
  if (itemA->score > itemB->score) {
    return -1; // itemA.higher ranked?
  } else if (itemB->score > itemA->score) {
    return 1;
  } else {
    if (strlen(itemA->name) < strlen(itemB->name)) {
      return -1;
    } else {
      return 1;
    }
  }
}
/**
 * returns the matching score of the name
 * retruns -1 if it doenst match
 * */
int get_score(char *input, file_item file) {
  int input_size = strlen(input);
  int file_size = strlen(file.name);
  int word_point = 0;
  int match_char = 0;
  double MAX_CHAR_SCORE = 100.0 / input_size;
  double CASE_PENALTY = 1;
  double SPACE_PENALTY = 1;
  double score = 0;
  for (int i = 0; i < input_size; i++) {
    for (int j = word_point; j < file_size; j++) {
      // check for general match
      if (tolower(input[i]) == tolower(file.name[j])) {
        // does case match?
        if (input[i] == file.name[j]) {
          // is the position right?
          if (j == word_point) {
            score += MAX_CHAR_SCORE;
          } else {
            score += MAX_CHAR_SCORE - (SPACE_PENALTY * j - word_point);
          }
        } else {
          // is the position right?
          if (j == word_point) {
            score += MAX_CHAR_SCORE - CASE_PENALTY;
          } else {
            score += MAX_CHAR_SCORE - CASE_PENALTY -
                     (SPACE_PENALTY * j - word_point);
          }
        }
        match_char = 1;
        word_point = j + 1;
        break;
      }
    }
    if (match_char == 0) {
      return -1;
    }
    match_char = 0;
  }
  return score;
}

file_list get_matching_list(char *input, file_list *list) {
  file_list filtered_list;

  create_List(&filtered_list);

  pthread_mutex_lock(&list->lock);
  for (int i = 0; i < list->count; i++) {
    double score = get_score(input, list->items[i]);
    if (score >= 0.0) {
      list->items[i].score = score;
      add_file_to_list(&filtered_list, list->items[i]);
    }
  }

  qsort(filtered_list.items, filtered_list.count, sizeof(file_item),
        compare_function);

  pthread_mutex_unlock(&list->lock);
  return filtered_list;
}

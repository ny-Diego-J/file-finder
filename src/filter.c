#include "file_item.h"
#include <ctype.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int compare_function(const void *a, const void *b) {
  const file_item *item_a = *(const file_item **)a;
  const file_item *item_b = *(const file_item **)b;

  if (item_a == NULL || item_b == NULL) {
    return 0;
  }

  if (item_a->score == 0 && item_b->score == 0) {
    return 0;
  }

  if (item_a->score > item_b->score) {
    return -1; // itemA.higher ranked?
  } else if (item_b->score > item_a->score) {
    return 1;
  } else {
    if (strlen(item_a->name) < strlen(item_b->name)) {
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
  bool match_char = false;
  double MAX_CHAR_SCORE = 100.0 / input_size;
  double CASE_PENALTY = 1;
  double SPACE_PENALTY = 1;
  double score = 0;
  for (int i = 0; i < input_size; i++) {
    for (int j = word_point; j < file_size; j++) {
      // check for general match
      if (tolower(input[i]) == tolower(file.name[j])) {
        score += MAX_CHAR_SCORE - (SPACE_PENALTY * (j - word_point));
        score -= input[i] == file.name[j] ? 0 : CASE_PENALTY;
        match_char = true;

        word_point = j + 1;
        break;
      }
    }
    if (!match_char) {
      return -1;
    }
    match_char = false;
  }
  score = fmax(score, 0.0);
  return score;
}

filtered_file_list get_matching_list(char *input, file_list *list) {
  filtered_file_list filtered_list;

  create_filtered_List(&filtered_list);

  pthread_mutex_lock(&list->lock);

  for (int i = 0; i < list->count; i++) {
    int score = (strlen(input) == 0) ? 0 : get_score(input, list->items[i]);
    if (score >= 0.0) {
      list->items[i].score = score;
      add_file_to_filtered_list(&filtered_list, &(list->items[i]));
    }
  }

  if (filtered_list.count > 1 && filtered_list.items != NULL) {
    qsort(filtered_list.items, filtered_list.count, sizeof(file_item *),
          compare_function);
  }

  pthread_mutex_unlock(&list->lock);
  return filtered_list;
}

#include "file_item.h"
#include <ctype.h>
#include <string.h>

int does_search_match(char *input, file_item file) {
  int input_size = strlen(input);
  int file_size = strlen(file.name);
  int word_point = 0;
  int match_char = 0;
  for (int i = 0; i < input_size; i++) {
    for (int j = word_point; j < file_size; j++) {
      if (tolower(input[i]) == tolower(file.name[j])) {
        match_char = 1;
        word_point = j + 1;
        break;
      }
    }
    if (match_char == 0) {
      return 0;
    }
    match_char = 0;
  }
  return 1;
}

#ifndef FILTER_H
#define FILTER_H
#include "file_item.h"
#include <ncurses.h>
filtered_file_list get_matching_list(char *input, file_list *list);
void print_highlighted(WINDOW *window, bool is_selected, char *name,
                       int filter_count, char *text, int x_offset);
#endif // FILTER_H

#include "file_item.h"
#include "filter.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
void drawui(file_list *list) {
  char text[1024] = "";
  int selectet_item = 0;

  // 1. Initialize ncurses and set up the virtual screen
  initscr();

  int input_height = 2;
  int input_width = COLS;
  int input_start_y = LINES - input_height;
  int input_start_x = 0;

  WINDOW *input_win =
      newwin(input_height, input_width, input_start_y, input_start_x);

  int file_start_y = 0;
  int file_start_x = 0;
  int file_width = COLS;
  int file_height = LINES - 2;
  WINDOW *file_win =
      newwin(file_height, file_width, file_start_y, file_start_x);

  cbreak();
  noecho();
  nodelay(input_win, TRUE);
  keypad(input_win, TRUE);

  mvwprintw(input_win, 0, 0, "> ");

  wrefresh(file_win);
  wrefresh(input_win);

  int pos = 0;
  int rem = 0;

  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  while (1) {
    werase(file_win);

    int filter_count = 0;
    pthread_mutex_lock(&list->lock);
    for (int i = 0; i < list->count; i++) {
      if (does_search_match(text, list->items[i])) {
        if (selectet_item == filter_count) {
          wattron(file_win, COLOR_PAIR(1));
        }
        mvwprintw(file_win, filter_count, 0, "%s", list->items[i].name);
        if (selectet_item == filter_count) {
          wattroff(file_win, COLOR_PAIR(1));
        }
        filter_count++;
      }
    }
    pthread_mutex_unlock(&list->lock);
    if (selectet_item > filter_count) {
      selectet_item = filter_count - 1;
    }

    wrefresh(file_win);

    int c = wgetch(input_win);
    if (c != ERR) {
      switch (c) {
      case KEY_BACKSPACE:
        if (pos == 0) {
        } else {

          text[--pos] = '\0';
          rem = 1;
        }
        break;
      case 10:
        pthread_mutex_lock(&list->lock);
        file_item file;
        int j = 0;
        for (int i = 0; i < list->count; i++) {
          if (does_search_match(text, list->items[i])) {
            if (selectet_item == j++) {
              file = list->items[i];
              break;
            }
          }
        }
        pthread_mutex_unlock(&list->lock);
        endwin();
        printf("%s/%s\n", file.path, file.name);
        exit(0);
        return;
        break;
      case KEY_UP:
        if (selectet_item > 0) {
          --selectet_item;
        }
        break;
      case KEY_DOWN:
        if (selectet_item < filter_count - 1) {
          ++selectet_item;
        } else {
          selectet_item = filter_count - 1;
        }
        break;
      default:
        text[pos++] = (char)c;
      }
      char display_buffer[1026];
      strcpy(display_buffer, "> ");
      strcat(display_buffer, text);
      mvwprintw(input_win, 0, 0, "%s", display_buffer);
      wrefresh(input_win);
      if (rem) {
        wclrtoeol(input_win);
        rem = 0;
      }
    }
  }

  endwin();
}

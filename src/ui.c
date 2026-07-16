#include "file_item.h"
#include "filter.h"
#include <math.h>
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
  int input_start_x = 0;
  int input_start_y = LINES - input_height;

  WINDOW *input_win =
      newwin(input_height, input_width, input_start_y, input_start_x);

  int file_height = LINES - 4;
  int file_width = COLS;
  int file_start_x = 0;
  int file_start_y = 0;
  WINDOW *file_win =
      newwin(file_height, file_width, file_start_y, file_start_x);

  int info_height = 2;
  int info_width = COLS;
  int info_start_x = 0;
  int info_start_y = input_start_y - info_height;

  WINDOW *info_win =
      newwin(info_height, info_width, info_start_y, info_start_x);

  cbreak();
  noecho();
  nodelay(input_win, TRUE);
  keypad(input_win, TRUE);
  curs_set(0);

  mvwprintw(input_win, 0, 0, "> ");

  wrefresh(file_win);
  wrefresh(info_win);
  wrefresh(input_win);
  werase(info_win);

  int pos = 0;
  int rem = 0;

  start_color();
  use_default_colors();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  int filter_count = 0;
  int offset = 0;
  int filter_amount = 0;
  while (1) {
    werase(file_win);

    filtered_file_list sorted_list = get_matching_list(text, list);

    filter_count = 0;
    pthread_mutex_lock(&list->lock);

    for (int i = offset; i < sorted_list.count; i++) {
      if (file_height == filter_count) {
        break;
      }
      if (selectet_item - offset == filter_count) {
        wattron(file_win, COLOR_PAIR(1));
      }
      mvwprintw(file_win, filter_count, 0, "%s", sorted_list.items[i]->name);
      if (selectet_item - offset == filter_count) {
        wattroff(file_win, COLOR_PAIR(1));
      }
      filter_count++;
    }

    filter_amount = 0;
    for (int i = 0; i < sorted_list.count; i++) {
      filter_amount++;
    }
    pthread_mutex_unlock(&list->lock);

    if (selectet_item > filter_amount) {
      selectet_item = filter_amount - 1;
      offset = 0;
    }

    werase(info_win);
    wattron(info_win, COLOR_PAIR(1));
    mvwprintw(info_win, 0, 0, "Files:   %d/%d", filter_amount, list->count);
    wattroff(info_win, COLOR_PAIR(1));
    wrefresh(info_win);

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
        // enter
      case 10:
        for (int i = 0; i < sorted_list.count; i++) {
          if (selectet_item == i) {
            endwin();
            printf("%s/%s\n", sorted_list.items[i]->path,
                   sorted_list.items[i]->name);
            exit(0);
            break;
          }
        }
        endwin();
        exit(0);
        return;
        break;
      case KEY_UP:
        if (selectet_item == 0) {
          break;
        }
        selectet_item--;
        if (offset > 0 && offset > selectet_item) {
          offset--;
        }
        break;
      case KEY_DOWN:
        if (selectet_item == filter_amount - 1) {
          break;
        }
        selectet_item++;
        if (file_height + offset < selectet_item + 1) {
          offset++;
        }

        break;
      default:
        if (c >= 32 && c <= 126) {
          text[pos++] = (char)c;
          text[pos] = '\0';
        }
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

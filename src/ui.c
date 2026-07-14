#include "FileItem.h"
#include <ncurses.h>
#include <stdio.h>
#include <string.h>
void drawui(FileList *list) {
  char text[1024] = "";

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

  // 2. Enable raw mode: catch keys instantly without waiting for Enter
  cbreak();

  // 3. Stop the terminal from automatically printing the keys you type
  noecho();

  // 4. Enable support for Arrow keys, F-keys, etc.
  nodelay(input_win, TRUE);
  keypad(input_win, TRUE);

  mvwprintw(input_win, 0, 0, "> ");

  wrefresh(file_win);
  wrefresh(input_win);

  int pos = 0;
  int rem = 0;
  while (1) {
    werase(file_win);

    for (int i = 0; i < list->count; i++) {
      mvwprintw(file_win, i, 0, "%s", list->items[i].name);
    }
    wrefresh(file_win);

    char c = wgetch(input_win);
    if (c != ERR) {
      switch (c) {
      case 7:
        if (pos == 0) {
        } else {

          text[--pos] = '\0';
          rem = 1;
        }
        break;
      case 10:
        printf("%s\n", text);
        // TODO: to go file
        endwin();
        return;
        break;
      default:
        text[pos++] = c;
      }
      char display_buffer[1026];
      strcpy(display_buffer, "> ");
      strcat(display_buffer, text);
      mvwprintw(input_win, 0, 0, display_buffer);
      wrefresh(input_win);
      if (rem) {
        wclrtoeol(input_win);
        rem = 0;
      }
    }
  }

  endwin();
}

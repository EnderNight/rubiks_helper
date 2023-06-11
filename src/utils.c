#include "utils.h"
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>


void print_version(void) {
  printw("Rubik's Helper v%d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_LABEL);
  refresh();
}

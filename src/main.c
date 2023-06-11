#include "utils.h"

#include <bits/time.h>
#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void init_ncurses(void) {
  initscr(); // Init

  cbreak(); // Disable input buffering
  
  noecho(); // Disable echo mode

  keypad(stdscr, TRUE); // Enable capture special strokes
}

void reset_ncurses(void) {
  endwin();
}

int main(int argc, char **argv) {

  init_ncurses();

  print_version();

  struct timespec start, end;


  // Main test loop
  printw("Press any key to start the timer...\n");
  refresh();
  int ch = getch();

  clock_gettime(CLOCK_MONOTONIC_RAW, &start);
  printw("GO!\n");
  refresh();

  ch = getch();

  clock_gettime(CLOCK_MONOTONIC_RAW, &end);

  double diff_sec = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

  printw("Elapsed time: %.3fs\n", diff_sec);
  refresh();

  ch = getch();


  reset_ncurses();

  return 0;
}

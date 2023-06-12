#include "utils.h"

#include <bits/time.h>
#include <curses.h>
#include <errno.h>
#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

struct timespec start_time, cross_time, f2l_time, oll_time, pll_time;

void init_nc(void) {
  initscr(); // Init

  cbreak(); // Disable input buffering

  noecho(); // Disable echo mode

  nodelay(stdscr, TRUE); // Disable waiting for input

  keypad(stdscr, TRUE); // Enable capture special strokes

  scrollok(stdscr, TRUE); // Enable scroll on default window
}

void restore_nc(void) { endwin(); }

void start_timer(void) { clock_gettime(CLOCK_MONOTONIC_RAW, &start_time); }

int msleep(long msec) {
  struct timespec ts;
  int res;

  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}

void wait_for_keypress(void) {
  while (getch() == ERR) {
    msleep(10);
  }
}

int wait_for_input_timer(void) {

  int ch, y, x;
  UNUSED(x);
  struct timespec timer_time;

  while ((ch = getch()) == ERR) {
    getyx(stdscr, y, x);
    clock_gettime(CLOCK_MONOTONIC_RAW, &timer_time);
    mvprintw(y, 0, "time: %.3fs",
             difftime(timer_time.tv_sec, start_time.tv_sec) +
                 (timer_time.tv_nsec - start_time.tv_nsec) / 1000000000.0);
    refresh();

    msleep(10);
  }

  return ch;
}

void print_step(int step) {

  switch (step) {
  case 1: {
    printw("\nFinished cross!\n");
    break;
  }
  case 2: {
    printw("\nFinished F2L!\n");
    break;
  }
  case 3: {
    printw("\nFinished OLL!\n");
    break;
  }
  case 4: {
    printw("\nFinished PLL!\n");
    break;
  }
  default: {
    printw("Unreachable\n");
  }
  }

  refresh();
}

int ask_restart(void) {
  int ch = getch(), y, x;
  UNUSED(x);

  getyx(stdscr, y, x);
  while (ch != 'y' && ch != 'n') {
    mvprintw(y, 0, "Would you like to restart ? (y/n) ");
    refresh();

    while ((ch = getch()) == ERR) {
    }
  }

  return ch == 'y';
}

// Step managing
void cross_step(void) {
  printw(
      "   __________  ____  __________\n  / ____/ __ \\/ __ \\/ ___/ ___/\n / "
      "/   / /_/ / / / /\\__ \\\\__ \\ \n/ /___/ _, _/ /_/ /___/ /__/ / "
      "\n\\____/_/ |_|\\____//____/____/\n");

  wait_for_input_timer();
}

void f2l_step(void) {
  printw(
      "    _________   __ \n   / ____/__ \\ / / \n  / /_   __/ // /  \n / __/ "
      " / __// /___\n/_/    /____/_____/\n");

  int ch;

  for (int i = 0; i < 4; ++i) {

    printw("\nCubes in position (1)\nCorner in position (2)\nEdge in position "
           "(3)\nCubes joined (4)\nCubes separated (5)\n");
    refresh();

    ch = wait_for_input_timer();

    switch (ch) {
    case '1': {
      printw("\nEdge in position (1)\nEdge not in position (2)\n");
      refresh();

      ch = wait_for_input_timer();

      switch (ch) {
      case '1': {
        printw("\nWhite face right (1)\nWhite face left (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\n\nRight: L2 U2 L U L' U L U2 L\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nLeft: L' U2 L' U' L U' L' U2 L2\n\n");
          refresh();
          break;
        }
        default:
          printw("\nSkip\n");
          refresh();
          break;
        }
        break;
      }
      case '2': {
        printw("\nWhite face right (1)\nleft (2)\ndown (3)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\n\nRight: L' U L' U' B' U B L2\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nLeft: R U' R U B U' B' R2\n\n");
          refresh();
          break;
        }
        case '3': {
          printw("\n\nLeft: R U R' U2 R U2 R' U F' U' F\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      default:
        printw("\nSkip\n");
        refresh();
        break;
      }
      break;
    }
    case '2': {
      printw("\nCorner white down (1)\nright (2)\nleft (3)\n");
      refresh();

      ch = wait_for_input_timer();

      switch (ch) {
      case '1': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\n\nRight: U' L' U L d R U' R'\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nLeft: U R U' R' d' L' U L\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '2': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\n\nLeft: R U R' U' R U R'\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nRight: L' U L U' L' U L\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '3': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\n\nLeft: R U' R' U R U' R'\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nRight: L' U' L U L' U' L\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      default: {
        printw("\nSkip\n");
        refresh();
        break;
      }
      }
      break;
    }
    case '3': {
      printw("\nEdge in correct position (1)\nnot (2)\n");
      refresh();

      ch = wait_for_input_timer();

      switch (ch) {

      case '1': {
        printw("\nCorner white up (1)\nright (2)\nleft (3)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {

        case '1': {
          printw("\n\nLeft: R2 U R2 U R2 U2 R2\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nRight: U L' U L U2 L' U L\n\n");
          refresh();
          break;
        }
        case '3': {
          printw("\n\nLeft: U' R U' R' U2 R U' R'\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '2': {
        printw("\nCorner white up (1)\nright (2)\nleft (3)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {

        case '1': {
          printw("\n\nLeft: F' U F R U2 R'\n\n");
          refresh();
          break;
        }
        case '2': {
          printw("\n\nRight: U L' U' L U' F U F'\n\n");
          refresh();
          break;
        }
        case '3': {
          printw("\n\nLeft: U' R U R' d R' U' R\n\n");
          refresh();
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      default: {
        printw("\nSkip\n");
        refresh();
        break;
      }
      }
      break;
    }
    case '4': {
      printw("\nCubes on the right (1)\nLeft (2)\n");
      refresh();

      ch = wait_for_input_timer();

      switch (ch) {
      case '1': {
        printw("\nEdge in correct face (1)\nnot (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\nCorner white face up (1)\nright (2)\nleft (3)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nLeft: R U2 R' U' R U R'\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: U' R U' R' U R U R'\n\n");
            refresh();
            break;
          }
          case '3': {
            printw("\n\nLeft: U R U' R'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        case '2': {
          printw("\nCorner white face up (1)\nright (2)\nleft (3)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: U2 L2 U2 L U L' U L2\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: R U' R' U2 F' U' F\n\n");
            refresh();
            break;
          }
          case '3': {
            printw("\n\nLeft: U' R U2 R' U F' U' F\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '2': {
        printw("\nEdge in correct face (1)\nnot (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\nCorner white face up (1)\nright (2)\nleft (3)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: L' U2 L U L' U' L\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nRight: U' L' U L\n\n");
            refresh();
            break;
          }
          case '3': {
            printw("\n\nRight: U L' U L U' L' U' L\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        case '2': {
          printw("\nCorner white face up (1)\nright (2)\nleft (3)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nLeft: U2 R2 U2 R' U' R U' R2\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nRight: U L' U2 L U' F U F'\n\n");
            refresh();
            break;
          }
          case '3': {
            printw("\n\nRight: L' U L U2 F U F'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      default: {
        printw("\nSkip\n");
        refresh();
        break;
      }
      }
      break;
    }
    case '5': {
      printw("\nCorner white face up (1)\nrigh (2)\nleft (3)\n");
      refresh();

      ch = wait_for_input_timer();

      switch (ch) {
      case '1': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: U2 L' U' L U' L' U L\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: U R U2 R' U R U' R'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        case '2': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: U' L' U2 L U' L' U L\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: U2 R U R' U R U' R'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '2': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: U L' U2 L U2 L' U L\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: R U R'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        case '2': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nRight: U L' U' L U2 L' U L\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nRight: U L' U L U' F U F'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      case '3': {
        printw("\nEdge right (1)\nleft (2)\n");
        refresh();

        ch = wait_for_input_timer();

        switch (ch) {
        case '1': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nLeft: U' R U' R' U F' U' F\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nLeft: U' R U R' U2 R U' R'\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        case '2': {
          printw("\nEdge correct face right (1)\nleft (2)\n");
          refresh();

          ch = wait_for_input_timer();

          switch (ch) {
          case '1': {
            printw("\n\nLeft: U' R U2 R' U2 R U' R'\n\n");
            refresh();
            break;
          }
          case '2': {
            printw("\n\nRight: L' U' L\n\n");
            refresh();
            break;
          }
          default: {
            printw("\nSkip\n");
            refresh();
            break;
          }
          }
          break;
        }
        default: {
          printw("\nSkip\n");
          refresh();
          break;
        }
        }
        break;
      }
      default: {
        printw("\nSkip\n");
        refresh();
        break;
      }
      }
      break;
    }
    default: {
      printw("\nSkip\n");
      refresh();
      break;
    }
    }

    wait_for_input_timer();
  }
}

void oll_step(void) {

  printw("   ____  __    __ \n  / __ \\/ /   / / \n / / / / /   / /  \n/ /_/ / "
         "/___/ /___\n\\____/_____/_____/\n");

  int ch;

  printw("\nCross (1)\nCross with one corner (2)\nCross with two corners same "
         "line (3)\nCross with two corners not same line (4)\n");
  refresh();

  ch = wait_for_input_timer();

  switch (ch) {
  case '1': {
    printw(
        "\nAll corner face each other (1)\n One corner face each other (2)\n");
    refresh();

    ch = wait_for_input_timer();

    if (ch == '1') {
      printw("\n\nR U R' U R U' R' U R U2 R'\n\n");
      refresh();
    } else if (ch == '2') {
      printw("\n\nR U2 R2 U' R2 U' R2 U2 R\n\n");
      refresh();
    } else {
      printw("\nSkip\n");
      refresh();
    }
    break;
  }
  case '2': {
    printw("\nCorner left (1)\nright (2)\n");
    refresh();

    ch = wait_for_input_timer();

    if (ch == '1') {
      printw("\n\nL' U2 L U L' U L\n\n");
      refresh();
    } else if (ch == '2') {
      printw("\n\nR U2 R' U' R U' R'\n\n");
      refresh();
    } else {
      printw("\nSkip\n");
      refresh();
    }
    break;
  }
  case '3': {
    printw("\nCorner face each other (1)\nCorner not face each other (2)\n");
    refresh();

    ch = wait_for_input_timer();

    if (ch == '1') {
      printw("\n\nl' U' L U R U' L' U\n\n");
      refresh();
    } else if (ch == '2') {
      printw("\n\nR2 D R' U2 R D' R' U2 R'\n\n");
      refresh();
    } else {
      printw("\nSkip\n");
      refresh();
    }
    break;
  }
  case '4': {
    printw("\n\nU2 R U2 R D R' U2 R D' R2\n\n");
    refresh();
    break;
  }
  default: {
    printw("\nSkip\n");
    refresh();
    break;
  }
  }

  wait_for_input_timer();
}

void pll_step(void) {
  printw("    ____  __    __ \n   / __ \\/ /   / / \n  / /_/ / /   / /  \n / "
         "____/ /___/ /___\n/_/   /_____/_____/\n");
  printw("\nEdges face each other (1)\nnot (2)\n");
  refresh();

  int ch;

  ch = wait_for_input_timer();

  switch (ch) {
  case '1': {
    printw("\n\nR U R' U' R' F R2 U' R' U' R U R' F'\n\n");
    refresh();
    break;
  }
  case '2': {
    printw("\nLeft to Right (1)\nRight to Left (2)\n");
    refresh();

    ch = wait_for_input_timer();

    switch (ch) {
    case '1': {
      printw("\n\nR2 U' R' U' R U R U R U' R\n\n");
      refresh();
      break;
    }
    case '2': {
      printw("\n\nR' U R' U' R' U' R' U R U R2\n\n");
      refresh();
      break;
    }
    default: {
      printw("\nSkip\n");
      refresh();
      break;
    }
    }
    break;
  }
  default: {
    printw("\nSkip\n");
    refresh();
    break;
  }
  }

  printw("\nAll corners in correct face (1)\nCorner face each other "
         "(2)\nSingle correct corner (3)\n");
  refresh();

  ch = wait_for_input_timer();

  switch (ch) {
  case '1': {
    printw("\n\nM2 U M2 U2 M2 U M2\n\n");
    refresh();
    break;
  }
  case '2': {
    printw("\n\nU->F U D R D' L D R' U' D' R U L' U' R'\n\n");
    refresh();
    break;
  }
  case '3': {
    printw("\nUpper left go bottom (1)\nGo right (2)\n");
    refresh();

    ch = wait_for_input_timer();

    if (ch == '1') {
      printw("\n\nD->F R2 D2 R U R' D2 R U' R\n\n");
    } else if (ch == '2') {
      printw("\n\nF->D R2 D2 R' U' R D2 R' U R'\n\n");
    } else {
      printw("\nSkip\n");
    }
    refresh();
    break;
  }
  default: {
    printw("\nSkip\n");
    refresh();
    break;
  }
  }

  wait_for_input_timer();
}

void manage_step(int step) {

  switch (step) {
  case 1: {
    cross_step();
    break;
  }
  case 2: {
    f2l_step();
    break;
  }
  case 3: {
    oll_step();
    break;
  }
  case 4: {
    pll_step();
    break;
  }
  default: {
    break;
  }
  }
}

void print_final_time(void) {
  struct timespec end_time;

  clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);

  printw("\nFinal time: %.3fs\n", difftime(end_time.tv_sec, start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1000000000.0);
  refresh();
}

void main_loop(void) {

  int step;

  do {
    // Reset app
    clear();
    print_version();
    step = 1;

    // Wait for start
    printw("Press any key to start the timer...\n");
    refresh();

    wait_for_keypress();

    start_timer();
    printw("GO!\n");
    refresh();

    // Main step loop
    while (step < 5) {
      manage_step(step);

      print_step(step);
      ++step;
    }

    printw("\nEND!\n");
    print_final_time();

  } while (ask_restart());
}

int main(void) {

  init_nc();

  main_loop();

  restore_nc();

  return 0;
}

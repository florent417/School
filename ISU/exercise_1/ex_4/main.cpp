//#include "part1.h"
//#include "part2.h"
//#include <iostream>
#include <ncurses.h>

int main(void)
{
//  part1();
//  part2();
  initscr();			/* Start curses mode 		  */
  printw("Hello World !!!");	/* Print Hello World		  */
  refresh();			/* Print it on to the real screen */
  getch();			/* Wait for user input */
  endwin();			/* End curses mode		  */

  return 0;
}

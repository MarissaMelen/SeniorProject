#include <curses.h>
#include "monsterstate.hpp"
#include "turn.hpp"

int main(){
  initscr();
  cbreak();
  nonl();
  int maxy;
  int maxx;
  getmaxyx(stdscr,maxy,maxx);
  WINDOW* monwin = newwin(maxy,maxx-(maxx/2),0,maxx/2);
  box(monwin,0,0);
  monster montype = {10,10,10,10,10,10,10,10,{water,water}};
  std::vector<status> foo;
  monsterstate enemy;
  enemy.name = (char*) "foo";
  enemy.basetype = montype;
  enemy.curhp = 10;
  std::vector<monsterstate> test;
  test.push_back(enemy);
  status sample;
  sample.type = burn;
  sample.level = 5;
  sample.duration = 10;
  sample(test[0].basetype);
  mvwprintw(monwin,1,1,"%s %d %d %d\n",test[0].name,test[0].curhp,test[0].basetype.maxhp,test[0].basetype.strength);
  //printw("%s %d %d %d",test[0].name,test[0].curhp,test[0].basetype.maxhp,test[0].basetype.strength);
  refresh();
  wrefresh(monwin);
  getch();
  test[0].effects.push_back(sample);
  passturn(test);
  mvwprintw(monwin,1,1,"%s %d %d %d\n",test[0].name,test[0].curhp,test[0].basetype.maxhp,test[0].basetype.strength);
  refresh();
  wrefresh(monwin);
  getch();
  wclear(monwin);
  delwin(monwin);
  clear();
  endwin();
}
  
		   

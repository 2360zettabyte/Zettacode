#include "main.h"

#ifndef CONTROLLERCUSTOM_H
#define CONTROLLERCUSTOM_H
class controllerCustom{
	public:
	int which;

	controllerCustom(int w);

  int rJoy();
  int lJoy();
  int btnA();
  int btnB();
  int btnX();
  int btnY();
  int r1();
  int r2();
  int l1();
  int l2();
  int up();
  int down();
  int left();
  int right();

};
#endif

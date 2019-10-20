#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"


int robL = 18;
void autonomous() {
  deploy();

  delay(1500);

  rollersVel(100);
  drive.translate(55-robL, 90, 50);
  drive.wait();
  delay(1000);
  drive.rotate(-90, 20);
  drive.wait();
  rollersVel(0);
  drive.translate(56-robL, 185, 75);
  drive.wait();
  drive.translate(7, 90, 50);
  drive.wait();
  delay(200);
  rollersVel(-25);
  anglerMoveDegree(85, 200);
  delay(1500);
  drive.translate(2, 90, 20);
  drive.wait();
  anglerMoveDegree(0, 200);
  delay(1500);

  rollersVel(-20);
  drive.translate(8, 270, 25);
  drive.wait();



}

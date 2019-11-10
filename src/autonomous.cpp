#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"


int robL = 18;
int basicAutonShimmy = 24;//inches
void autonomous() { drive.driveLock(true);
  if(mainAuton ==0){ //By default it will deploy the tray & Rollers



    deploy();
  }

  if(mainAuton==1){ //Back auton: Stacks 4 cubes
    double speedMult = 2;

    deploy();



    rollersVel(150);

    drive.translate(55-robL, 85, 50*speedMult);
    drive.wait();
    delay(200);


    drive.rotate(-90, 20*speedMult);
    drive.wait();
    rollersVel(0);
    delay(10);
    drive.translate(54-robL, 175, 100);
    drive.wait();
    drive.translate(7, 90, 75);
    drive.wait();
    delay(200);
    rollersVel(-25);
    anglerMoveDegree(85, 200);
    delay(2000);
    drive.translate(2, 90, 20);
    drive.wait();
    anglerMoveDegree(0, 200);
    delay(1500);

    rollersVel(-20);
    drive.translate(8, 270, 25);
    drive.wait();
  }

  if(mainAuton ==2){ //[2] Front auton: Preload in goalzone & desploy; [3]Back auton: Preload in goalzone & deploy
    drive.translate(-26,-10, 50);
    drive.wait();
    delay(500);
    drive.translate(26,10, 50);
    drive.wait();
    delay(500);
    deploy();
  }
  if(mainAuton ==3){ //[2] Front auton: Preload in goalzone & desploy; [3]Back auton: Preload in goalzone & deploy
    drive.translate(26,10, 50);
    drive.wait();
    delay(500);
    drive.translate(-26,-10, 50);
    drive.wait();
    delay(500);
    deploy();
  }


  drive.driveLock(false);
}

#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"


int robL = 18;
int basicAutonShimmy = 24;//inches



void stack(int amount){
  if(amount==3){
    anglerForceMoveDegree(80, 70);
    while(anglerGetDegree()<50){}
    rollersVel(-10);
    while(anglerGetDegree()<70){}
    delay(1000);
  }

  if(amount==5){
    anglerForceMoveDegree(80, 70);
    rollersVel(10);
    while(anglerGetDegree()<50){}
    rollersVel(-10);
    while(anglerGetDegree()<79){}
    delay(500);
  }
}
void autonomous() {
  int r = isRed;
  int b = !isRed;

  drive.driveLock(true);


  if(mainAuton==0){

  }

  if(mainAuton ==1){
    armsMoveDegree(14,50);
    rollersVel(200);
    drive.translate(50, 90, 100);
    drive.wait();

    rollerR.move_relative((700)+(500), 100);
    rollerL.move_relative((700)+(500), 100);
    drive.rotate((r*90)+(b*-90), 30);


    drive.wait();
    delay(500);
    rollersVel(0);

    rollerR.move_relative(-400, 50);
    rollerL.move_relative(-400, 50);

    drive.translate((r*50)+(b*50), (r*0)+(b*180), 100);

    drive.wait();

    drive.translate((r*11)+(b*11), (r*92)+(b*90), 100);

    drive.wait();

    armsMoveDegree(0, 50);
    stack(5);
    anglerForceMoveDegree(0, 100);
    rollersVel(-30);
    drive.translate(8, 270, 25);
    drive.wait();
    rollersVel(0);
    anglerForceMoveDegree(0, 100);

  }

  if(mainAuton==2){
    armsMoveDegree(12,80);
    anglerForceMoveDegree(15,  50);
    delay(500);
    rollersVel(120);
    drive.translate(20, 90, 100);
    drive.wait();
    delay(700);
    drive.rotate((r*-92)+(b*92), 30);
    rollersVel(150);
    drive.wait();
    anglerForceMoveDegree(0,  50);
    drive.translate(22, 90, 50);
    drive.wait();


    rollerR.move_relative(-400, 50);
    rollerL.move_relative(-400, 50);
    drive.translate((r*16)+(b*18), (r*180)+(b*0), 50);
    drive.wait();
    armsMoveDegree(0, 80);
    drive.translate((r*5.5)+(b*7), 90, 50);
    drive.wait();

    stack(3);
    anglerForceMoveDegree(0, 100);
    rollersVel(-30);
    drive.translate(8, 270, 25);
    drive.wait();
    rollersVel(0);
    anglerForceMoveDegree(0, 100);

  }
  //-----------------------
  if(mainAuton==5){ //Back auton: Stacks 4 cubes
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
    anglerForceMoveDegree(85, 200);
    delay(2000);
    drive.translate(2, 90, 20);
    drive.wait();
    anglerForceMoveDegree(0, 200);
    delay(1500);

    rollersVel(-20);
    drive.translate(8, 270, 25);
    drive.wait();
  }

  if(mainAuton ==3){ //[2] Front auton: Preload in goalzone & desploy; [3]Back auton: Preload in goalzone & deploy
    drive.translate(-26,-10, 50);
    drive.wait();
    delay(500);
    drive.translate(26,10, 50);
    drive.wait();
    delay(500);
    deploy();
  }
  if(mainAuton ==7){ //[2] Front auton: Preload in goalzone & desploy; [3]Back auton: Preload in goalzone & deploy
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

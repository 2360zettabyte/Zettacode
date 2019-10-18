#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"
using namespace pros::literals;

double armsMult = 7*1800;
double anglerMult = 21*1800;

//--Angler Arms Loop Variables--//
int error = 5; //Degrees of error allowed for the arms to begin to move
int prevAnglerDegree = 0;
int newAnglerDegree = 0;
int anglerSpeed = 0;
int prevArmsDegree = 0;
int newArmsDegree = 0;
int armsSpeed = 0;

double noCollisionDegree = 13;

void opcontrol(){
  while(true){
    //--Deploy Robot--//
    if(cont.btnA()){
      armsMoveDegree(20, 200);
      delay(1000);
      anglerMoveDegree(10, 200);
      armsMoveDegree(0,100);
      delay(1000);
      newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 26; armsSpeed = 100;
    }
    if(cont.btnB()){

      autonomous();
    }

    if(cont.btnX()){
      rollersVel(-20);
      drive.translate(8, 270, 25);
      drive.wait();
    }


    //--Driver control of the X-Drive--//
    drive.arcadeDrive(cont.joy4(), cont.joy3(), cont.joy1());

    //--Control the angling of the Tray--//
    if(armsGetDegree()<3){
      if(cont.l1()){ newAnglerDegree = 84; anglerSpeed = 100; }
      if(cont.l2()){ newAnglerDegree = 0; anglerSpeed = 100; }

    }

    //--Control the  anglingg of the Rollers
    if(cont.up()){
      newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 85; armsSpeed = 100; //  armsMoveDegree(85, 100);
    }
    if(cont.right()){
      newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 65; armsSpeed = 100; //  armsMoveDegree(65, 100);
    }
    if(cont.down()){
      newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 0; armsSpeed = 100;//armsMoveDegree(0, 100);
    }
    if(armsGetDegree()<3&&prevArmsDegree==newArmsDegree && prevArmsDegree==0 && newAnglerDegree==prevAnglerDegree && prevAnglerDegree == noCollisionDegree){
      newAnglerDegree = 0;
    }
    if(cont.r2()){
      rollersVel(200);
    }else if(cont.r1()){
      rollersVel(-100);
    }else{
      rollersVel(0);
    }
    //rollerR.move_velocity(200*(cont.r2()-cont.r1()));
    //rollerL.move_velocity(200*(cont.r2()-cont.r1()));

    //--Angler Arms Loop--//
    if((prevAnglerDegree != newAnglerDegree)){
      anglerMoveDegree(newAnglerDegree,anglerSpeed);
      prevAnglerDegree = newAnglerDegree;
    }
    if(fabs(anglerGetDegree()-prevAnglerDegree)<error){
      if((prevArmsDegree != newArmsDegree) ){
        armsMoveDegree(newArmsDegree,armsSpeed);
        prevArmsDegree = newArmsDegree;
      }
    }




    //--End of Loop--//

    delay(10);
  }
}

#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"
using namespace pros::literals;

double armsMult = 7*1800;
double anglerMult = 21*1800;

//--Angler Arms Loop Variables--//
int error = 5; //Degrees of error allowed for the arms to begin to move


int prevArmsDegree = 0;
int newArmsDegree = 0;
int armsSpeed = 0;
bool rollersEnabled = true;

double noCollisionDegree = 17;

void opcontrol(){
  armsMoveDegree(noCollisionDegree,50);
  while(true){
    //--Deploy Robot--//
    if(cont.btnA()){
      armsMoveDegree(noCollisionDegree,50);
      arms.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    if(cont.btnB()){

      armsMoveDegree(0, 25);
      arms.set_brake_mode(E_MOTOR_BRAKE_COAST);

    }

    if(cont.btnX()){
      rollersVel(-20);
      drive.translate(8, 270, 25);
      drive.wait();
    }


    if(cont.btnY()){
      rollersMoveInches(-5, 50);
      rollersEnabled = false;
    }


    //--Driver control of the X-Drive--//
    drive.arcadeDrive(cont.joy4(), cont.joy3(), cont.joy1());

    //--Control the angling of the Tray--//
    if(armsGetDegree()<15+10){
      if(cont.l1()){ anglerMoveDegree(84, 100);}
      if(cont.l2()){ anglerMoveDegree(0, 100); }

    }

    //--Control the  anglingg of the Rollers
    if(cont.up()){
      //newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 85; armsSpeed = 100; //  armsMoveDegree(85, 100);
    }
    if(cont.right()){
      //newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 65; armsSpeed = 100; //  armsMoveDegree(65, 100);
    }
    if(cont.down()){
      //newAnglerDegree = noCollisionDegree; anglerSpeed = 100;
      newArmsDegree = 0; armsSpeed = 100;//armsMoveDegree(0, 100);
    }
    if(rollersEnabled){
      if(cont.r2()){
        rollersVel(150);
      }else if(cont.r1()){
        rollersVel(-100);
      }else{
        rollersVel(0);
      }
    }else{
      rollersEnabled = fabs(rollerR.get_target_position()-rollerR.get_position())<5;
    }
    //rollerR.move_velocity(200*(cont.r2()-cont.r1()));
    //rollerL.move_velocity(200*(cont.r2()-cont.r1()));

    //--Angler Arms Loop--//


    if(newArmsDegree!=prevArmsDegree){
      if(newArmsDegree==0){
        if(armsGetDegree()>30){
          armsMoveDegree(30-error, 100);
        }else{
          anglerMoveDegree(0, 100);
          armsMoveDegree(noCollisionDegree, 100);
          prevArmsDegree = newArmsDegree;
        }
      }else{
        if(armsGetDegree()>30-error){
          anglerMoveDegree(noCollisionDegree, 100);
          if(anglerGetDegree()>error){
            armsMoveDegree(newArmsDegree, 80);
            prevArmsDegree=newArmsDegree;
          }
        }else{
          if(anglerGetDegree()<error){
            armsMoveDegree(30,100);
          }else{
            anglerMoveDegree(noCollisionDegree, 100);
          }

        }
      }
    }


    /*
    if((prevAnglerDegree != newAnglerDegree)){
    anglerMoveDegree(newAnglerDegree,anglerSpeed);
    prevAnglerDegree = newAnglerDegree;
  }
  if(fabs(anglerGetDegree()-prevAnglerDegree)<error){
  if((prevArmsDegree != newArmsDegree) ){
  armsMoveDegree(newArmsDegree,armsSpeed);
  prevArmsDegree = newArmsDegree;
}
}*/




//--End of Loop--//

delay(10);
}
}

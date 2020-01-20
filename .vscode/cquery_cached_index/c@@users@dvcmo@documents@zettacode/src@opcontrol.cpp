#include "main.h"
#include "MyHeaders/global.h"
#include "Subsystems/subsystems.h"
//#include "PID-master/cpp/PID.h"
using namespace pros::literals;

double armsMult = 7*1800;
double anglerMult = 21*1800;

//--Angler Arms Loop Variables--//
int error = 5; //Degrees of error allowed for the arms to begin to move


int prevArmsDegree = 0;
int newArmsDegree = 0;
int armsSpeed = 0;
bool rollersEnabled = true;

const double  PICK_CUBE_DEGREE= 13;
const double TILT_TRAY_DEGREE = 5;

void opcontrol(){
  //armsMoveDegree(noCollisionDegree,50);
  anglerPID.setTarget(0);
  while(true){
    drive.arcadeDrive(cont.joy4(), cont.joy3(), cont.joy1());

    if(cont.left()&&cont.right()){ //1 inch track
      double units = (2.1 * 1800)/(1.5 * 3.1416);
      angler.move_absolute(units, 50);
      delay(2000);
      angler.move_absolute(0, 50);
      while(fabs(angler.get_position())>5){}
    }

    if(cont.btnX()){
      rollersVel(-30);
      drive.translate(8, 270, 25);
      drive.wait();
    }

    if(cont.btnY()){
      autonomous();
    }

    if(cont.r2()){
        rollersVel(150);
        if(anglerGetDegree()<17&&armsGetDegree()<10  &&fabs(angler.get_position()-anglerPID.getTarget())<300 ){
          armsMoveDegree(PICK_CUBE_DEGREE, 50);
        }
      }else if(cont.r1()){
        rollersVel(-100);
      }else{
        rollersVel(0);
      }
    if(armsGetDegree()<PICK_CUBE_DEGREE+10){
      if(cont.l1()){
        anglerMoveDegree(92, 100);
        armsMoveDegree(TILT_TRAY_DEGREE, 25);
      }
      if(cont.l2()){
        anglerMoveDegree(0, 100);
      }
    }

    if(anglerGetDegree()<=17){
      if(cont.up()){
        anglerMoveDegree(17, 100);
        armsMoveDegree(105, 100);

      }
      if(cont.right()){
        anglerMoveDegree(17, 100);
        armsMoveDegree(90, 100);
      }
      if(cont.down()){
        if(armsGetDegree()>PICK_CUBE_DEGREE){
          anglerMoveDegree(17, 100);
          armsMoveDegree(PICK_CUBE_DEGREE, 100);
        }
      }
    }




    anglerPID.tick();
    delay(25);
      //--End of Loop--//
  }
}

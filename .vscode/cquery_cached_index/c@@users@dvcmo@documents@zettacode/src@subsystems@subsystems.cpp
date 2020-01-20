#include "main.h"
#include "../MyHeaders/global.h"
//#include "../PID-master/cpp/PID.h"

//------------Config-------------//
double armsMa = 7;
double anglerMa = 15;
double armsResting = 8;
int allowedError = 5;
//-------------------------------//

double armsTarget = 0;
double anglerTarget = 0;
double anglerPrevDegree = 0;
double anglerVelocity = 0;

/*---------------------------------------------------------------------------------
| --BASIC METHODS--
---------------------------------------------------------------------------------*/
//--angler--//

int anglerSource(){	return angler.get_position();	} //FOR PID USE
void anglerOutput(int output){	angler.move_voltage(output);	}//FOR PID USE

double anglerGetDegree(){   return ((angler.get_position()*360.0)/1800.0)/anglerMa; }


void anglerMoveDegree(double degree, int speed){
  anglerPID.setEnabled(true);
  anglerPID.setTarget((degree/360.0)*1800*anglerMa);
  anglerPID.setOutputBounds(-12000*(speed/100.0), 12000*(speed/100.0));
  anglerTarget = degree; anglerVelocity = speed;
  anglerPrevDegree = anglerGetDegree()*(anglerGetDegree()>0);
}

void anglerForceMoveDegree(double degree, int speed){
  anglerPID.setEnabled(false);
  angler.move_absolute((degree/360.0)*1800*anglerMa, speed);
  anglerTarget = degree; anglerVelocity = speed;
  anglerPrevDegree = anglerGetDegree()*(anglerGetDegree()>0);
}

void an(double degree, int speed){
  anglerPID.setEnabled(true);
  anglerPID.setTarget((degree/360.0)*1800*anglerMa);
  anglerPID.setOutputBounds(-12000*(speed/100.0), 12000*(speed/100.0));
  anglerTarget = degree; anglerVelocity = speed;
  anglerPrevDegree = anglerGetDegree()*(anglerGetDegree()>0);
}

//--arms--//
void armsMoveDegree(double degree, int speed){   arms.move_absolute((degree/360.0)*1800*armsMa, speed); armsTarget = degree; }
double armsGetDegree(){   return (arms.get_position()/1800.0)/armsMa*360.0; }
//--arms--//
void rollersVel(int velocity){rollerL.move_velocity(velocity+0);
                              rollerR.move_velocity(velocity+0);
                              delay(10);}

void rollersMoveInches(double inches, int speed){
  rollerL.move_relative(((inches/3)*900), speed);
  rollerR.move_relative(((inches/3)*900), speed);
}

/*------------------------------------------------------------------
| --COMPLEX METHODS--
------------------------------------------------------------------*/


void armsAnglerWait(){
while(fabs(angler.get_position()-angler.get_target_position())>5){
  delay(10);
}
while(fabs(arms.get_position()-arms.get_target_position())>5){
  delay(10);
}

}
void deploy(){


}

/*
From the motor product page:
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
/*------------------------------------------------------------------
| --Method Name--
|   - Description
------------------------------------------------------------------*/

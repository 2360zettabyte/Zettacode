#include "main.h"
#include "../MyHeaders/global.h"

//------------Config-------------//
double armsMa = 7;
double anglerMa = 21;
double armsResting = 8;
int allowedError = 5;
//-------------------------------//

double armsTarget = 0;
double anglerTarget = 0;

/*---------------------------------------------------------------------------------
| --BASIC METHODS--
---------------------------------------------------------------------------------*/
//--angler--//
void anglerMoveDegree(double degree, int speed){   angler.move_absolute((degree/360.0)*1800*anglerMa, speed); anglerTarget = degree; }
double anglerGetDegree(){   return (angler.get_position()/1800.0)/anglerMa*360.0; }
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
  double armsDeployment =50;
  double anglerDepoloyment =30;


armsMoveDegree(20, 100);
armsAnglerWait();
armsMoveDegree(0, 100);
armsAnglerWait();
delay(500);
rollersVel(-200);
armsMoveDegree(45,100);
armsAnglerWait();
delay(500);
armsMoveDegree(0, 100);
rollersVel(0);
delay(500);

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

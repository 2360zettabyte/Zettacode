#include "main.h"
#include "../MyHeaders/global.h"

//------------Config-------------//
double armsMa = 7;
double anglerMa = 21;
double armsResting = 8;
//-------------------------------//

/*---------------------------------------------------------------------------------
| --BASIC METHODS--
---------------------------------------------------------------------------------*/
//--angler--//
void anglerMoveDegree(int degree, int speed){   angler.move_absolute((degree/360.0)*1800*anglerMa, speed);  }
double anglerGetDegree(){   return (angler.get_position()/1800.0)/anglerMa*360.0; }
//--arms--//
void armsMoveDegree(int degree, int speed){   arms.move_absolute((degree/360.0)*1800*armsMa, speed);  }
double armsGetDegree(){   return (arms.get_position()/1800.0)/armsMa*360.0; }

/*------------------------------------------------------------------
| --COMPLEX METHODS--
------------------------------------------------------------------*/
void deploy(){
  double armsDeployment =50;
  double anglerDepoloyment =30;

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

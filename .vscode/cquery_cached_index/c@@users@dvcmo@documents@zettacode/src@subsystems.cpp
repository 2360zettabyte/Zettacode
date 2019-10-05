#include "main.h"
#include "MyHeaders/global.h"

//------------Config-------------//
double armsMa = 7;
double anglerMa = 21;
double armsResting = 8;
//-------------------------------//

//-----Calibration Variables-----//

//-------------------------------//

/*---------------------------------------------------------------------------------
| --anglerMoveDegree--
|   - turns the angler to a specific degree with relation to its starting position
---------------------------------------------------------------------------------*/
void anglerMoveDegree(int degree, int speed){
  angler.move_absolute((degree/360.0)*1800*anglerMa, speed);
}

/*---------------------------------------------------------------------------------
| --anglerMoveDegree--
|   - turns the angler to a specific degree with relation to its starting position
---------------------------------------------------------------------------------*/
void armsMoveDegree(int degree, int speed){
  arms.move_absolute((degree/360.0)*1800*armsMa, speed);
}

/*------------------------------------------------------------------
| --Deploy--
|   - Deploys both the arms and the Tray
------------------------------------------------------------------*/
void deploy(){
  double armsDeployment =50;
  double anglerDepoloyment =30;

  anglerMoveDegree(anglerDepoloyment, 100);
  while(fabs(angler.get_position()-anglerDepoloyment)>10){
    delay(5);
  }
  armsMoveDegree(armsDeployment, 100);

  while(fabs(arms.get_position()-armsDeployment)>10){
    delay(5);
  }
  //delay(500);
  arms.set_brake_mode(E_MOTOR_BRAKE_COAST);
  armsMoveDegree(armsResting, 100);
  anglerMoveDegree(0, 50);

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

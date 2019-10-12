#include "main.h"
//#include "../MyHeaders/global.h"

/*---------------------------------------------------------------------------------
| --Arms Basic Methods--
|   - Various basic methods for the arms that are used for more complex methods
---------------------------------------------------------------------------------*/
extern void armsMoveDegree(double degree, int speed);
    //moves the arms at an absolute given speed to a given degree relative to its starting position
extern double armsGetDegree();
    //returns a degree (as a double) of the arms relative to their starting angle

/*---------------------------------------------------------------------------------
| --Angler Basic Methods--
|   - Various basic methods for the angler that are used for more complex methods
---------------------------------------------------------------------------------*/
extern void anglerMoveDegree(double degree, int speed);
    //moves the angler at an absolute given speed to a given degree relative to its starting position
extern double anglerGetDegree();
    //returns a degree (as a double) of the angler relative to its starting angle

/*------------------------------------------------------------------
| --Deploy--
|   - Deploys both the arms and the Tray
------------------------------------------------------------------*/
extern void deploy();

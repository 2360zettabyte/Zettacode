#include "main.h"
#include "../Controller/controllerCustom.h"
#include "../XDrive/XDrive.h"
//#include "../XDrive/PID-master/cpp/PID.h"

//--Motor Definitions--//
extern Motor angler;
extern Motor rollerR;//hello
extern Motor rollerL;
extern Motor arms;

extern XDrive drive;
extern PIDController<int> anglerPID;

//--Controller Declarations--//
extern controllerCustom cont;
extern controllerCustom partner;

//--Constants--//
extern const double wheelDiameter;
extern const double pi;

//--Global Variables--//
extern int mainAuton;
extern bool redTeam;
extern int isRed;

//--Global Methods--//
extern void UIFunc();

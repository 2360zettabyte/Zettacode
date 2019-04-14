#include "main.h"
#include "../Controller/controllerCustom.h"

//--Motor Definitions--//
extern Motor left_back_drive;
extern Motor left_front_drive;
extern Motor right_back_drive;
extern Motor right_front_drive;
extern Motor puncher;
extern Motor intake;
extern Motor aimer;
extern Motor arm;

//--Controller Declarations--//
extern controllerCustom cont;
extern controllerCustom partner;

//--Constants--//
extern const double wheelDiameter;
extern const double pi;

//--Global Variables--//
extern int mainAuton;

//--Global Methods--//
extern void UIFunc();

#include "main.h"
#include "MyHeaders/global.h"
#include "Controller/controllerCustom.h"
#include "XDrive/XDrive.h"

#define KF 0//<---- PID TESTING
#define KP 1.0f//<---- PID TESTING
#define KI 0.001f//<---- PID TESTING
#define KD 0.1f//<---- PID TESTING

//--Motor Definitions--//
XDrive drive(15,6,12,13); //RF RB LF LB
Motor angler(16,true);
Motor rollerR(10,true);
Motor rollerL(1);
Motor arms(14,true);



//--Controller Declarations--//
controllerCustom cont(1);
controllerCustom partner(2);

//--Constants--//
const double wheelDiameter = 4;
const double pi = 3.141593;

//--Global Variables--//
int mainAuton = 0;

void initialize(){  //First Thing to Run
  pros::Task userInterface((task_fn_t)UIFunc);
  angler.set_gearing(E_MOTOR_GEARSET_36);
  arms.set_gearing(E_MOTOR_GEARSET_36);

  rollerL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  rollerR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

}

void disabled() {} //in Between Autonomous & opControl
void competition_initialize() {} //After Initialize but Before Autonumous

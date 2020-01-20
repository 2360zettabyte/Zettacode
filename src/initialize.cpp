#include "main.h"
#include "MyHeaders/global.h"
#include "Controller/controllerCustom.h"
#include "XDrive/XDrive.h"
#include "Subsystems/subsystems.h"
//#include "PID-master/cpp/PID.h"

/*
#define KF 0//<---- PID TESTING
#define KP 0.4f//<---- PID TESTING
#define KI 0.1f//<---- PID TESTING
#define KD 1.0f//<---- PID TESTING
*/

//--Motor Definitions--//


Motor angler(7,true);
Motor rollerR(12,true);
Motor rollerL(5);
Motor arms(6,true);

XDrive drive(13,8,15,9); //RF RB LF LB
PIDController<int> anglerPID(5, 0.01, 5, anglerSource, anglerOutput); //P I D

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

  anglerPID.setOutputBounded(true);
	anglerPID.setOutputBounds(-12000, 12000);

  angler.set_gearing(E_MOTOR_GEARSET_36);
  arms.set_gearing(E_MOTOR_GEARSET_36);

  arms.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

  rollerL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  rollerR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

}

void disabled() {} //in Between Autonomous & opControl
void competition_initialize() {} //After Initialize but Before Autonumous

#include "main.h"
#include "controllerCustom.h"

controllerCustom::controllerCustom(int w){
	which = w;
}
int controllerCustom::joy1(){
	int m = pros::c::controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_X);
	int p = pros::c::controller_get_analog(E_CONTROLLER_PARTNER, E_CONTROLLER_ANALOG_RIGHT_X);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::joy2(){
	int m = pros::c::controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_RIGHT_Y);
	int p = pros::c::controller_get_analog(E_CONTROLLER_PARTNER, E_CONTROLLER_ANALOG_RIGHT_Y);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::joy3(){
	int m = pros::c::controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_Y);
	int p = pros::c::controller_get_analog(E_CONTROLLER_PARTNER, E_CONTROLLER_ANALOG_LEFT_Y);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::joy4(){
	int m = pros::c::controller_get_analog(E_CONTROLLER_MASTER, E_CONTROLLER_ANALOG_LEFT_X);
	int p = pros::c::controller_get_analog(E_CONTROLLER_PARTNER, E_CONTROLLER_ANALOG_LEFT_X);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::btnA(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_A);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_A);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::btnB(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_B);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_B);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::btnX(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_X);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_X);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::btnY(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_Y);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_Y);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::r1(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R1);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_R1);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::r2(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_R2);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_R2);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::l1(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L1);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_L1);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::l2(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_L2);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_L2);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::up(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_UP);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_UP);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::down(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_DOWN);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_DOWN);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::left(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_LEFT);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_LEFT);
	return ((which==1)*m) + ((which==2)*p);
}
int controllerCustom::right(){
	int m = pros::c::controller_get_digital(E_CONTROLLER_MASTER, E_CONTROLLER_DIGITAL_RIGHT);
	int p = pros::c::controller_get_digital(E_CONTROLLER_PARTNER, E_CONTROLLER_DIGITAL_RIGHT);
	return ((which==1)*m) + ((which==2)*p);
}

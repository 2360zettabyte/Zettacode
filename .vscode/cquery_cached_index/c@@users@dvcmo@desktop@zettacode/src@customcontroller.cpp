#include "main.h"

class ControllerCustom{
	public:
	int which;
	int rJoy;
	int lJoy;
	int joy4;
	double btnA;
	double btnB;
	double btnX;
	double btnY;
	double r1;
	double r2;
	double l1;
	double l2;
	double up;
	double down;
	double right;
	double left;

	double battery;

	ControllerCustom(int w){
	  which = w;//banana
	}

	void update(){
		if(which==1){
			pros::Controller master(pros::E_CONTROLLER_MASTER);
			rJoy = master.get_analog(ANALOG_RIGHT_Y);
			lJoy = master.get_analog(ANALOG_LEFT_Y);
			joy4 = master.get_analog(ANALOG_LEFT_X);
			btnA = master.get_digital(DIGITAL_A);
			btnB = master.get_digital(DIGITAL_B);
			btnX = master.get_digital(DIGITAL_X);
			btnY = master.get_digital(DIGITAL_Y);
			r1 = master.get_digital(DIGITAL_R1);
			r2 = master.get_digital(DIGITAL_R2);
			l1 = master.get_digital(DIGITAL_L1);
			l2 = master.get_digital(DIGITAL_L2);
			up = master.get_digital(DIGITAL_UP);
			down = master.get_digital(DIGITAL_DOWN);
			right = master.get_digital(DIGITAL_RIGHT);
			left = master.get_digital(DIGITAL_LEFT);
			battery = master.get_battery_level();
		}
		if(which==2){
			pros::Controller partner(pros::E_CONTROLLER_PARTNER);
			rJoy = partner.get_analog(ANALOG_RIGHT_Y);
			lJoy = partner.get_analog(ANALOG_LEFT_Y);
			joy4 = partner.get_analog(ANALOG_LEFT_X);
			btnA = partner.get_digital(DIGITAL_A);
			btnB = partner.get_digital(DIGITAL_B);
			btnX = partner.get_digital(DIGITAL_X);
			btnY = partner.get_digital(DIGITAL_Y);
			r1 = partner.get_digital(DIGITAL_R1);
			r2 = partner.get_digital(DIGITAL_R2);
			l1 = partner.get_digital(DIGITAL_L1);
			l2 = partner.get_digital(DIGITAL_L2);
			up = partner.get_digital(DIGITAL_UP);
			down = partner.get_digital(DIGITAL_DOWN);
			right = partner.get_digital(DIGITAL_RIGHT);
			left = partner.get_digital(DIGITAL_LEFT);
		}
	}
};
/* if(which==1){
	rJoy = master.get_analog(ANALOG_RIGHT_Y);
	lJoy = master.get_analog(ANALOG_LEFT_Y);
	joy4 = master.get_analog(ANALOG_LEFT_X);
	btnA = master.get_digital(DIGITAL_A);
	btnB = master.get_digital(DIGITAL_B);
	btnX = master.get_digital(DIGITAL_X);
	btnY = master.get_digital(DIGITAL_Y);
	r1 = master.get_digital(DIGITAL_R1);
	r2 = master.get_digital(DIGITAL_R2);
	l1 = master.get_digital(DIGITAL_L1);
	l2 = master.get_digital(DIGITAL_L2);
	up = master.get_digital(DIGITAL_UP);
	down = master.get_digital(DIGITAL_DOWN);
	right = master.get_digital(DIGITAL_RIGHT);
	left = master.get_digital(DIGITAL_LEFT);
	battery = master.get_battery_level();
}
if(which==2){
	pros::Controller partner(pros::E_CONTROLLER_PARTNER);
	rJoy = partner.get_analog(ANALOG_RIGHT_Y);
	lJoy = partner.get_analog(ANALOG_LEFT_Y);
	joy4 = partner.get_analog(ANALOG_LEFT_X);
	btnA = partner.get_digital(DIGITAL_A);
	btnB = partner.get_digital(DIGITAL_B);
	btnX = partner.get_digital(DIGITAL_X);
	btnY = partner.get_digital(DIGITAL_Y);
	r1 = partner.get_digital(DIGITAL_R1);
	r2 = partner.get_digital(DIGITAL_R2);
	l1 = partner.get_digital(DIGITAL_L1);
	l2 = partner.get_digital(DIGITAL_L2);
	up = partner.get_digital(DIGITAL_UP);
	down = partner.get_digital(DIGITAL_DOWN);
	right = partner.get_digital(DIGITAL_RIGHT);
	left = partner.get_digital(DIGITAL_LEFT);
}*/

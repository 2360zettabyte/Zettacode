#include "main.h"
#include "MyHeaders/global.h"
using namespace pros::literals;

bool aimerCalibrated = false;
int aimerTarget;
int shotA = 345;
int shotB = 0;
int shotX = 191;

int shotA2 = 900;
int shotB2 = 200;
int shotX2 = 703;
/*------------------------------------------------------------------
| --aimTick Method--
|   - moves the motor a certain amount of ticks
------------------------------------------------------------------*/
void aimTick(int ticks, bool wait){

  if(!aimerCalibrated){
    aimer.move_velocity(-50);
    delay(600);
    aimer.tare_position();
    aimer.move_velocity(0);
    aimerCalibrated = true;
  }

  int direction = 2*(ticks>aimer.get_position())-1;
  aimerTarget = ticks;

  aimer.move_absolute(ticks, 200);
  aimer.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  if(!wait){return;}

  if(direction>1){
    while(aimer.get_position()<ticks-10){}
  }
  if(direction<1){
    while(aimer.get_position()>ticks+10){}
  }
  delay(600);
}


/*------------------------------------------------------------------
| --shoot Method--
|   - Fires a ball from the puncher
------------------------------------------------------------------*/
void shoot(){


  delay(20);
  puncher.tare_position();
  intake.tare_position();

  puncher.move(127);
  intake.move_velocity(0);

  while(puncher.get_position()<1000){
    delay(05);
  }
  puncher.move_velocity(0);
  puncher.set_brake_mode(E_MOTOR_BRAKE_COAST);

}

/*------------------------------------------------------------------
| --forceShoot Method--
|   - Fires a ball from the puncher
------------------------------------------------------------------*/
void doubleShot(){


  puncher.tare_position();
  intake.tare_position();
  int currentPosition = shotA;
  int secondPosition = shotA2;

  if(aimerTarget==shotB){
    currentPosition = shotB;
    secondPosition = shotB2;
  }
  if(aimerTarget==shotX){
    currentPosition = shotX;
    secondPosition = shotX2;
  }

  aimTick(currentPosition, false);
  intake.move_velocity(0);
  puncher.move_absolute(900, 200);
  while(puncher.get_position()<900){
    delay(10);
  }

  intake.move_velocity(200);
  aimTick(secondPosition, true);

  puncher.tare_position();
  puncher.move_absolute(900, 200);
  while(puncher.get_position()<900){
    delay(10);
  }

  aimTick(currentPosition, false);
  intake.move_velocity(0);
  puncher.move_velocity(0);
  puncher.set_brake_mode(E_MOTOR_BRAKE_COAST);
}



void opcontrol() {


	bool lowCapMode = false;
	int armMode = 1; //0 = disable and put away, 1 = carry/prevent puncher from hitting; 2 = lowCaps
	bool storeMode = false;
	bool sensorTapped = false;

	bool pressed = false;
	int phase = 0;
	int timer1 = 0;
	int pos = 0;
	bool timer1_ended = false;

	arm.tare_position();
	aimer.tare_position();
	puncher.tare_position();
	//aimer.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	aimTick(shotA, false);
	//aimer.move_velocity(0);


  while(true){

    //--Auton Testing--//
		//if(!cont.up&&cont.right&&!cont.down&&cont.left){
		if (cont.btnB()){
			autonomous();
		}

		//--Drive--//
		right_back_drive.move( cont.rJoy() );
		right_front_drive.move( cont.rJoy() );

		left_back_drive.move( cont.lJoy()  );
		left_front_drive.move( cont.lJoy()  );

		//--Aimer--//
		if(partner.btnA()==1&&partner.up()){aimTick(shotA, false);}//if(cont.btnA==1){aimTick(shotA, false);}
		if(partner.btnB()==1&&partner.up()){aimTick(shotB, false);}//if(cont.btnB==1){aimTick(shotB, false);}
		if(partner.btnX()==1&&partner.up()){aimTick(shotX, false);}//if(cont.btnX==1){aimTick(shotX, false);}
		if(partner.btnA()==1&&partner.down()){aimTick(shotA2, false);}
		if(partner.btnB()==1&&partner.down()){aimTick(shotB2, false);}
		if(partner.btnX()==1&&partner.down()){aimTick(shotX2, false);}



    std::cout << aimer.get_position()<< std::endl;
		//std::string text = "Aimer: "+ std::to_string(aimer.get_position()) + " Ticks";
		//contConsole(text.c_str());

		//--Puncher--//
		puncher.set_brake_mode(MOTOR_BRAKE_COAST); //puncher.move_velocity(200*cont.r2);
		if(cont.r2()){shoot();}
		if(cont.r1()){doubleShot();}


    //--Intake--//

		if(cont.right()){
			storeMode = true;
			sensorTapped = false;
		}

		if(storeMode){
			if(cont.l1() || cont.l2()){
				storeMode = false;
			}
			if(!sensorTapped){
				intake.move_velocity(-50);
				sensorTapped = pros::c::adi_digital_read(1);
				if(sensorTapped){
					intake.tare_position();
				}
			}else{
				intake.move_absolute(200, 200);
				if(intake.get_position()>=200){
					storeMode=false;
				}
			}

		}else{
			if(cont.l1()){
				intake.move_velocity(200);
			}
			if(cont.l2()){
				intake.move_velocity(-150);
			}
			if((!cont.l1()&&!cont.l2())){
				intake.move_velocity(0);
			}
		}

		//--Arm--//
		if(armMode == 0){ //Disable
			if(arm.get_position()>((30/360.0)*(64/12.0)*900)){
				arm.move_absolute(10,200);
			}
			if(arm.get_position()<((30/360.0)*(64/12.0)*900)){
				arm.move_velocity(0);
				arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
			}

		}
		if(armMode == 1){ //Post Mode
		  arm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
		  if(partner.lJoy()<10&&partner.lJoy()>-10){
		    arm.move_absolute(((45/360.0)*(64/12.0)*900),100);
		  }
			if(partner.lJoy()>10){
		    arm.move_absolute(((165/360.0)*(64/12.0)*900),50);
		  }
			if(partner.lJoy()<-10){
		    arm.move_absolute( ((0/360.0)*(64/12.0)*900) ,100);
		  }
		}
		if(armMode == 2){ //Low Cap Mode
		  arm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
		  if(partner.l1()){
		    arm.move_absolute(((195/360.0)*(64/12.0)*900),200);
		  }
			if(partner.l2()){
		    arm.move_absolute(((225/360.0)*(64/12.0)*900),200);
		  }
		  if(!partner.l1()&&!partner.l2()){
				if(arm.get_position()<((250/360.0)*(64/12.0)*900)){
					arm.move_absolute(((270/360.0)*(64/12.0)*900),200);
				}
				if(arm.get_position()>((250/360.0)*(64/12.0)*900)){
					arm.move_velocity(0);
					arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
				}
		  }
		}
		if(cont.left()){armMode = 0;}
		if(cont.down()){armMode = 1;}
		if(cont.up()){armMode = 2;}


		//--Vision Sensor Testing--//

	}
}

/*
---PID LEARNING----
Try #1:

#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f

void initialize() {
  pros::Motor motor (1);
  pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD); <--- KF the input???
  motor.set_pos_pid(pid);
}





HOW TO CONSOLE
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str());
  arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		arm.move_velocity(200*(cont.l1-cont.l2));
indexButton = pros::c::adi_digital_read(indexSensor);
*/

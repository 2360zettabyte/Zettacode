#include "main.h"
//#include "../MyHeaders/global.h"
#include "XDrive.h"

int motorArray[4];
int u = 10;
double pid[]{ 5 , 0.015, 6 }; //PID 5 , 0.05, 5

XDrive::XDrive(int rightFront, int rightBack, int leftFront, int leftBack)
: right_front(rightFront), right_back(rightBack), left_front(leftFront), left_back(leftBack),  //This is called member initializion list
right_frontPID(pid[0], pid[1], pid[2], RF_PID_Input, RF_PID_Output), right_backPID(pid[0], pid[1], pid[2], RB_PID_Input, RB_PID_Output),
left_frontPID(pid[0], pid[1], pid[2], LF_PID_Input, LF_PID_Output),left_backPID(pid[0], pid[1], pid[2], LB_PID_Input, LB_PID_Output)
{
	mechanicalAdvantage = 1;
	allowedError = 10;
	wheelDiameter = 4;
	yDistance = 0;
	xDistance = 0;
	xSpeed = 0;
	ySpeed = 0;
	pi  = 3.141593;
	motorArray[0] = rightFront;
	motorArray[1] = rightBack;
	motorArray[2] = leftFront;
	motorArray[3] = leftBack;
}

int XDrive::RF_PID_Input(){return pros::c::motor_get_position(motorArray[0]);}
int XDrive::RB_PID_Input(){return pros::c::motor_get_position(motorArray[1]);}
int XDrive::LF_PID_Input(){return pros::c::motor_get_position(motorArray[2]);}
int XDrive::LB_PID_Input(){return pros::c::motor_get_position(motorArray[3]);}

void XDrive::RF_PID_Output(int output){ pros::c::motor_move_voltage(motorArray[0], output); }
void XDrive::RB_PID_Output(int output){ pros::c::motor_move_voltage(motorArray[1], output); }
void XDrive::LF_PID_Output(int output){ pros::c::motor_move_voltage(motorArray[2], output); }
void XDrive::LB_PID_Output(int output){ pros::c::motor_move_voltage(motorArray[3], output); }


void XDrive::translate(int inches, int degree, int speed){
	double cosine;
	double sine;
	int sinMult = 1; //this values are for adjusting values in other quadrants
	int cosMult = 1;

	//--Fixing the speed Value--//
	speed = abs(speed);
	if(speed>200){speed = 200;}

	//--Converting the angle value--//
	degree = degree + 45; //Needed because the Math considers the chasis as a + not an X
	if(inches<0){ //this line anticipates the user putting in a negative inches value to go backwards
		degree = degree+180;
		inches = abs(inches);
	}
	if(degree<0){degree=360+degree;}			//This two lines make sure that the degree is in the domain (0,360)
	while(degree>360){degree=degree-360;}

	if(90<degree && degree<=180){ //This chunk of code makes the angle always be in quadrant 1 but adjusts the multipliers for later
		degree = 180-degree;
		cosMult = -1;
	}
	if(180<degree && degree<=270){
		degree = degree-180;
		sinMult = -1;
		cosMult = -1;
	}
	if(270<degree && degree<=360){
		degree = 360-degree;
		sinMult = -1;
	}


	//--Transforming into Motor Values--//
	cosine = cos(degree*pi/180);
	sine = sin(degree*pi/180);

	ySpeed = speed * sine * sinMult;
	xSpeed = speed * cosine * cosMult;

	double rotations = inches/(wheelDiameter*pi);
	double encoderUnits = rotations*900*mechanicalAdvantage;
	yDistance = encoderUnits * sine * sinMult; //gets the motors going at the right speed for the right quadrant
	xDistance = encoderUnits * cosine * cosMult;

	//--Setting the Motors--//
	left_back.tare_position();
	left_front.tare_position();
	right_back.tare_position();
	right_front.tare_position();

	left_back.move_absolute(-xDistance, -fabs(xSpeed)); // These are the cosine Motors
	right_front.move_absolute(xDistance, fabs(xSpeed));

	right_back.move_absolute(-yDistance, -fabs(ySpeed)); // These are the Sine Motors
	left_front.move_absolute(yDistance, fabs(ySpeed));
}

void XDrive::rotate(int degrees,int speed){
	xSpeed = speed;
	ySpeed = speed;
	double wheel_diagonal = sqrt(pow(wheelDiameter,2)/2);
	double frameLength = 6+wheel_diagonal;
	double frameWidth = 4.5+wheel_diagonal;
	double opposingWheelDistance = 14;

	int direction = 2*(degrees>0)-1; // Gets the directionallity of degrees: clockwise being positive
	degrees = abs(degrees);//Gets the absolute of degrees
	double radius = sqrt( pow(frameLength/2,2) + pow(frameWidth/2,2) ); //radius out of the "circle"
	double arcLength = radius*(degrees*(pi/180)); //gets the Arc length that the wheel will have to travel after converting the degrees to radians

	double rotations = arcLength/(wheelDiameter*pi); //gets the amount of revolutions the wheel will have to do in order to move the arc length
	double encoderUnits = rotations*900*mechanicalAdvantage; //Gets the amount of encoder units that the motor will have to get to in order to complete the amount of revolutions

	left_front.move_velocity(0);
	left_back.move_velocity(0);
	right_front.move_velocity(0);
	right_back.move_velocity(0);

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	speed = abs(speed); //Anticipating the user plugging in a negative speed
	encoderUnits = encoderUnits*direction;
	left_front.move_absolute(encoderUnits,speed);
	left_back.move_absolute(encoderUnits,speed);
	right_front.move_absolute(encoderUnits,speed);
	right_back.move_absolute(encoderUnits,speed);

	xDistance = encoderUnits;
	yDistance = encoderUnits;
}


void XDrive::translatePID(int inches, int degree, int speed){
	right_frontPID.setEnabled(true); right_backPID.setEnabled(true);left_frontPID.setEnabled(true);left_backPID.setEnabled(true);
	double cosine;
	double sine;
	int sinMult = 1; //this values are for adjusting values in other quadrants
	int cosMult = 1;

	//--Fixing the speed Value--//
	speed = abs(speed);
	if(speed>200){speed = 200;}

	//--Converting the angle value--//
	degree = degree + 45; //Needed because the Math considers the chasis as a + not an X
	if(inches<0){ //this line anticipates the user putting in a negative inches value to go backwards
		degree = degree+180;
		inches = abs(inches);
	}
	if(degree<0){degree=360+degree;}			//This two lines make sure that the degree is in the domain (0,360)
	while(degree>360){degree=degree-360;}

	if(90<degree && degree<=180){ //This chunk of code makes the angle always be in quadrant 1 but adjusts the multipliers for later
		degree = 180-degree;
		cosMult = -1;
	}
	if(180<degree && degree<=270){
		degree = degree-180;
		sinMult = -1;
		cosMult = -1;
	}
	if(270<degree && degree<=360){
		degree = 360-degree;
		sinMult = -1;
	}
	//--Transforming into Motor Values--//
	cosine = cos(degree*pi/180);
	sine = sin(degree*pi/180);

	ySpeed = speed * sine ;
	xSpeed = speed * cosine ;

	left_backPID.setOutputBounded(true); left_backPID.setOutputBounds(-(xSpeed/200.0)*12000, (xSpeed/200.0)*12000); // These are the cosine Motors
	right_frontPID.setOutputBounded(true); right_frontPID.setOutputBounds(-(xSpeed/200.0)*12000, (xSpeed/200.0)*12000);

	right_backPID.setOutputBounded(true); right_backPID.setOutputBounds(-(ySpeed/200.0)*12000, (ySpeed/200.0)*12000);// These are the Sine Motors
	left_frontPID.setOutputBounded(true); left_frontPID.setOutputBounds(-(ySpeed/200.0)*12000, (ySpeed/200.0)*12000);

	double rotations = inches/(wheelDiameter*pi);
	double encoderUnits = rotations*900*mechanicalAdvantage;
	yDistance = encoderUnits * sine * sinMult; //gets the motors going at the right speed for the right quadrant
	xDistance = encoderUnits * cosine * cosMult;

	//--Setting the Motors--//
	left_back.tare_position();
	left_front.tare_position();
	right_back.tare_position();
	right_front.tare_position();

	left_backPID.setTarget(-xDistance); // These are the cosine Motors
	right_frontPID.setTarget(xDistance);

	right_backPID.setTarget(-yDistance); // These are the Sine Motors
	left_frontPID.setTarget(yDistance);
}

void XDrive::rotatePID(int degrees,int speed){
	xSpeed = speed;
	ySpeed = speed;
	double wheel_diagonal = sqrt(pow(wheelDiameter,2)/2);
	double frameLength = 6+wheel_diagonal;
	double frameWidth = 4.5+wheel_diagonal;
	double opposingWheelDistance = 14;

	int direction = 2*(degrees>0)-1; // Gets the directionallity of degrees: clockwise being positive
	degrees = abs(degrees);//Gets the absolute of degrees
	double radius = sqrt( pow(frameLength/2,2) + pow(frameWidth/2,2) ); //radius out of the "circle"
	double arcLength = radius*(degrees*(pi/180)); //gets the Arc length that the wheel will have to travel after converting the degrees to radians

	double rotations = arcLength/(wheelDiameter*pi); //gets the amount of revolutions the wheel will have to do in order to move the arc length
	double encoderUnits = rotations*900*mechanicalAdvantage; //Gets the amount of encoder units that the motor will have to get to in order to complete the amount of revolutions

	left_front.move_velocity(0);
	left_back.move_velocity(0);
	right_front.move_velocity(0);
	right_back.move_velocity(0);

	left_front.tare_position();
	left_back.tare_position();
	right_front.tare_position();
	right_back.tare_position();

	speed = abs(speed); //Anticipating the user plugging in a negative speed
	encoderUnits = encoderUnits*direction;
	left_front.move_absolute(encoderUnits,speed);
	left_back.move_absolute(encoderUnits,speed);
	right_front.move_absolute(encoderUnits,speed);
	right_back.move_absolute(encoderUnits,speed);

	xDistance = encoderUnits;
	yDistance = encoderUnits;
}


void XDrive::arcadeDrive(int x, int y, int rotate){
	int xPos = abs(x)*(x>0);
	int xNeg = abs(x)*(x<0);
	int yPos = abs(y)*(y>0);
	int yNeg = abs(y)*(y<0);
	double posSlope = sqrt(pow(xPos,2)+pow(yPos,2)) - sqrt(pow(xNeg,2)+pow(yNeg,2));
	double negSlope = sqrt(pow(xNeg,2)+pow(yPos,2)) - sqrt(pow(xPos,2)+pow(yNeg,2));
	posSlope = (posSlope/170) *127;
	negSlope = (negSlope/170) *127;
	left_back.move(negSlope + rotate); // These are the cosine Motors
	right_front.move(-negSlope + rotate);
	right_back.move(-posSlope + rotate); // These are the Sine Motors
	left_front.move(posSlope + rotate);

}

// void XDrive::tankDrive(int left, int right, int strafeL, int strafeR){
//
// 	double strafeAmount = 200*(((strafeL + strafeR )/2.0)/127.0);
// 	left_front.move_velocity(200*(left/127.0) + strafeAmount);
// 	left_back.move_velocity(200*(left/127.0) - strafeAmount);
// 	right_front.move_velocity(-200*(left/127.0) - strafeAmount);
// 	right_back.move_velocity(-200*(left/127.0) + strafeAmount);
//
// }

void XDrive::wait(){
	bool err1,err2,err3,err4;
	bool timer = true;
	double startingTime = millis();
	int slowDownMult = 4; //The bigger the greater the acceleration
	int xVel = right_front.get_target_velocity();
	int yVel = left_front.get_target_velocity();
	double calculatedTime = ((sqrt(pow(xDistance,2) + pow(yDistance,2)))/900) / (right_front.get_target_velocity()*900*60) + 3;

	while(timer &&(err1||err2||err3||err4)){
		timer = (millis() - startingTime) < calculatedTime*1000;

		double slowdown = sin( pi*( right_front.get_position()/fabs(xDistance) ) )/slowDownMult + (1 - (1/slowDownMult));

		err1 = fabs(fabs(left_back.get_position())-fabs(xDistance))>allowedError;
		err2 = fabs(fabs(right_front.get_position())-fabs(xDistance))>allowedError;
		err3 = fabs(fabs(right_back.get_position())-fabs(yDistance))>allowedError;
		err4 = fabs(fabs(left_front.get_position())-fabs(yDistance))>allowedError;


		delay(10);
	}

	delay(20);
	left_back.tare_position();left_front.tare_position();right_back.tare_position();right_front.tare_position();
	xDistance = 0;
	yDistance = 0;
	delay(20);

}


void XDrive::waitPID(){
	// bool err1,err2,err3,err4;
	// bool timer = true;
	// double startingTime = millis();
	// int slowDownMult = 4; //The bigger the greater the acceleration
	// int xVel = right_front.get_target_velocity();
	// int yVel = left_front.get_target_velocity();
	// double calculatedTime = ((sqrt(pow(xDistance,2) + pow(yDistance,2)))/900) / (right_front.get_target_velocity()*900*60) + 3;
	//
	// while(timer &&(err1||err2||err3||err4||false)){
	// 	timer = true;//(millis() - startingTime) < calculatedTime*1000;
	//
	// 	double slowdown = sin( pi*( right_front.get_position()/fabs(xDistance) ) )/slowDownMult + (1 - (1/slowDownMult));
	//
	// 	err1 = fabs(fabs(left_back.get_position())-fabs(xDistance))>allowedError;
	// 	err2 = fabs(fabs(right_front.get_position())-fabs(xDistance))>allowedError;
	// 	err3 = fabs(fabs(right_back.get_position())-fabs(yDistance))>allowedError;
	// 	err4 = fabs(fabs(left_front.get_position())-fabs(yDistance))>allowedError;
	//
	// 	std::cout << fabs(left_back.get_position())-fabs(xDistance) << ", ";
	// 	std::cout << fabs(right_front.get_position())-fabs(xDistance) << ", ";
	// 	std::cout << fabs(right_back.get_position())-fabs(yDistance) << ", ";
	// 	std::cout << fabs(left_front.get_position())-fabs(yDistance) <<std::endl;
	//
	//
	// 	left_backPID.tick();
	// 	right_frontPID.tick();
	//
	// 	right_backPID.tick();
	// 	left_frontPID.tick();
	// 	delay(10);
	// }
	//
	// delay(50);
	// right_frontPID.setEnabled(false); right_backPID.setEnabled(false);left_frontPID.setEnabled(false);left_backPID.setEnabled(false);
	// left_back.tare_position();left_front.tare_position();right_back.tare_position();right_front.tare_position();
	// xDistance = 0;
	// yDistance = 0;
	// delay(20);

	bool err1,err2,err3,err4;
	double sX = 12000*(fabs(xSpeed)/200.0);
	double sY = 12000*(fabs(ySpeed)/200.0);
	double m = 3000;
	double u = 80;
	int n = 350;
	// int x = fabs(fabs(right_front.get_position())-fabs(xDistance));
	// int y = fabs(fabs(left_front.get_position())-fabs(yDistance));
	// int xSlowdown;
	// int ySlowdown;
	// int xMod;
	// int yMod;
	int xPolarity = 2*(xSpeed>0)-1;
	int yPolarity = 2*(ySpeed>0)-1;
	int rf, lb, rb, lf;
	int rfSlowdown, lbSlowdown, rbSlowdown, lfSlowdown;
	int rfMod, lbMod, rbMod, lfMod;
	left_back.move_velocity(0);
	right_front.move_velocity(0);
	right_back.move_velocity(0);
	left_front.move_velocity(0);

	while(err1||err2||err3||err4){

		rf = fabs(fabs(right_front.get_position())-fabs(xDistance));
		rfSlowdown = fabs(((sX-m)/pi)*atanf((1/u)*(rf-(u*7)))+((sX-m)/2)+m);
		rfMod = fabs(((m-rfSlowdown)/pi)*atanf((2/u)*(rf-fabs(xDistance)))+((rfSlowdown-m)/2)+m);

		lb = fabs(fabs(left_back.get_position())-fabs(xDistance));
		lbSlowdown = fabs(((sX-m)/pi)*atanf((1/u)*(lb-(u*7)))+((sX-m)/2)+m);
		lbMod = fabs(((m-lbSlowdown)/pi)*atanf((2/u)*(lb-fabs(xDistance)))+((lbSlowdown-m)/2)+m);

		rb = fabs(fabs(right_back.get_position())-fabs(yDistance));
		rbSlowdown = fabs(((sY-m)/pi)*atanf((1/u)*(rb-(u*7)))+((sY-m)/2)+m);
		rbMod = fabs(((m-rbSlowdown)/pi)*atanf((2/u)*(rb-fabs(yDistance)))+((rbSlowdown-m)/2)+m);

		lf = fabs(fabs(left_front.get_position())-fabs(yDistance));
		lfSlowdown = fabs(((sY-m)/pi)*atanf((1/u)*(lf-(u*7)))+((sY-m)/2)+m);
		lfMod = fabs(((m-lfSlowdown)/pi)*atanf((2/u)*(lf-fabs(yDistance)))+((lfSlowdown-m)/2)+m);

		if(lb>n){left_back.move_voltage(-lbMod*xPolarity);}else{left_back.move_absolute(-xDistance, 40);}
		if(rf>n){right_front.move_voltage(lbMod*xPolarity);}else{right_front.move_absolute(xDistance, 40);}
		if(rb>n){right_back.move_voltage(-rbMod*yPolarity);}else{right_back.move_absolute(-yDistance, 40);}
		if(lf>n){left_front.move_voltage(rbMod*yPolarity);}else{left_front.move_absolute(yDistance, 40);}

		err1 = fabs(fabs(left_back.get_position())-fabs(xDistance))>allowedError;
		err2 = fabs(fabs(right_front.get_position())-fabs(xDistance))>allowedError;
		err3 = fabs(fabs(right_back.get_position())-fabs(yDistance))>allowedError;
		err4 = fabs(fabs(left_front.get_position())-fabs(yDistance))>allowedError;
		delay(10);
	}

	left_back.move_velocity(0);
	right_front.move_velocity(0);
	right_back.move_velocity(0);
	left_front.move_velocity(0);
	left_back.tare_position();left_front.tare_position();right_back.tare_position();right_front.tare_position();
	delay(50);
}


void XDrive::driveLock(bool enabled){
	if(enabled){
		left_front.move_velocity(0);left_back.move_velocity(0);right_front.move_velocity(0);right_back.move_velocity(0);
		left_front.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		left_back.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		right_front.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		right_back.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	}else{
		left_front.set_brake_mode(E_MOTOR_BRAKE_COAST);
		left_back.set_brake_mode(E_MOTOR_BRAKE_COAST);
		right_front.set_brake_mode(E_MOTOR_BRAKE_COAST);
		right_back.set_brake_mode(E_MOTOR_BRAKE_COAST);
	}
}

#include "main.h"
//#include "../MyHeaders/global.h"
#include "XDrive.h"

XDrive::XDrive(int rightfront, int rightBack, int leftFront, int LeftBack)
: left_back(LeftBack), left_front(leftFront), right_back(rightBack), right_front(rightfront) //This is called member initializion list
{
	mechanicalAdvantage = 1;
	allowedError = 10;
	wheelDiameter = 4;
	yDistance = 0;
	xDistance = 0;
	pi  = 3.141593;//testing to see if changes work
}

void XDrive::translate(int inches, int degree, int speed){
	double ySpeed;
	double xSpeed;

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

	ySpeed = speed * sine;
	xSpeed = speed * cosine;

	double rotations = inches/(wheelDiameter*pi);
	double encoderUnits = rotations*900*mechanicalAdvantage;
	yDistance = encoderUnits * sine * sinMult; //gets the motors going at the right speed for the right quadrant
	xDistance = encoderUnits * cosine * cosMult;

	//--Setting the Motors--//
	left_back.tare_position();
	left_front.tare_position();
	right_back.tare_position();
	right_front.tare_position();

	left_back.move_absolute(-xDistance, -xSpeed); // These are the cosine Motors
	right_front.move_absolute(xDistance, xSpeed);

	right_back.move_absolute(-yDistance, -ySpeed); // These are the Sine Motors
	left_front.move_absolute(yDistance, ySpeed);

	//--Feedback Loop--//


}

void XDrive::rotate(int degrees,int speed){

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

void XDrive::tankDrive(int left, int right, int strafeL, int strafeR){

	double strafeAmount = 200*(((strafeL + strafeR )/2.0)/127.0);
	left_front.move_velocity(200*(left/127.0) + strafeAmount);
	left_back.move_velocity(200*(left/127.0) - strafeAmount);
	right_front.move_velocity(-200*(left/127.0) - strafeAmount);
	right_back.move_velocity(-200*(left/127.0) + strafeAmount);

}

void XDrive::wait(){
	bool err1,err2,err3,err4;
	bool timer = true;
	double startingTime = millis();
	int slowDownMult = 4; //The bigger the greater the acceleration
	int xVel = right_front.get_target_velocity();
	int yVel = left_front.get_target_velocity();
	double calculatedTime = ((sqrt(pow(xDistance,2) + pow(yDistance,2)))/900) / (right_front.get_target_velocity()*900*60) + 5;

	while(timer &&(err1||err2||err3||err4)){
		timer = (millis() - startingTime) < calculatedTime*1000;

		double slowdown = sin( pi*( right_front.get_position()/fabs(xDistance) ) )/slowDownMult + (1 - (1/slowDownMult));

/*
		left_front.modify_profiled_velocity(yVel*slowdown);
		left_back.modify_profiled_velocity(xVel*slowdown);
		right_front.modify_profiled_velocity(xVel*slowdown);
		right_back.modify_profiled_velocity(yVel*slowdown);*/

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
	/*
	while(err1||err2||err3||err4){
	err1 = fabs(left_back.get_position()+xDistance)>allowedError;
	err2 = fabs(right_front.get_position()-xDistance)>allowedError;
	err3 = fabs(right_back.get_position()+yDistance)>allowedError;
	err4 = fabs(left_front.get_position()-yDistance)>allowedError;
}*/
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

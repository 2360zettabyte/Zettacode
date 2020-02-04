#include "main.h"
#include "PID-master/cpp/PID.h"

#ifndef XDRIVE_H
#define XDRIVE_H
class XDrive{
	private://internal variables that can not be direcctly accessed
		Motor left_back;
		Motor left_front;
		Motor right_back;
		Motor right_front;
		PIDController<int> left_backPID;
		PIDController<int> left_frontPID;
		PIDController<int> right_backPID;
		PIDController<int> right_frontPID;
		double mechanicalAdvantage;
		int allowedError;
		double wheelDiameter;
		double pi;
		double yDistance;
		double xDistance;
		double xSpeed;
		double ySpeed;

	public: //methods that can be accessed by outside code

	XDrive(int rightfront, int rightBack, int leftFront, int LeftBack);

	void translate(int inches, int degree, int speed);
	void rotate(int degrees,int speed);

	void translatePID(int inches, int degree, int speed);
	void rotatePID(int degrees,int speed);

	void arcadeDrive(int x, int y, int rotate);

	//void tankDrive(int left, int right, int strafeL, int strafesR);

	void wait();

	void waitPID();

	void driveLock(bool enabled);


	static int RF_PID_Input();
	static int RB_PID_Input();
	static int LF_PID_Input();
	static int LB_PID_Input();

	static void RF_PID_Output(int output);
	static void RB_PID_Output(int output);
	static void LF_PID_Output(int output);
	static void LB_PID_Output(int output);



};
#endif
 //10,9,20,12

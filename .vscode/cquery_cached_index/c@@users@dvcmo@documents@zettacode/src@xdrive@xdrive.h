#include "main.h"

#ifndef XDRIVE_H
#define XDRIVE_H
class XDrive{
	private://internal variables that can not be direcctly accessed
		Motor left_back;
		Motor left_front;
		Motor right_back;
		Motor right_front;
		double mechanicalAdvantage;
		int allowedError;
		double wheelDiameter;
		double pi;
		double yDistance;
		double xDistance;

	public: //methods that can be accessed by outside code

	XDrive(int rightfront, int rightBack, int leftFront, int LeftBack);

	void translate(int inches, int degree, int speed);

	void rotate(int degrees,int speed);

	void arcadeDrive(int x, int y, int rotate);

	void tankDrive(int left, int right, int strafeL, int strafesR);

	void wait();
};
#endif
 //10,9,20,12

#include "main.h"

void lift(int iSpeed) 
{
    motorSet(R_LIFT, iSpeed);
    motorSet(L_LIFT, iSpeed);
}

void mogo(int iSpeed) 
{
    motorSet(MOGO, iSpeed);
}

void roller(int iSpeed) 
{
    motorSet(INTAKE, -iSpeed);
}

void mani(int iSpeed) 
{
    motorSet(L_MANI, iSpeed);
    motorSet(R_MANI, -iSpeed);
}

//PD//

pid sArmPID;
int
iArmPID( int iDes ) {
	sArmPID.kP         = 0.021;
  sArmPID.kD         = 0.38;
	sArmPID.current    = analogRead(LIFT_POT);
	sArmPID.error      = iDes - sArmPID.current;
	sArmPID.derivative = sArmPID.error - sArmPID.lastError;
  sArmPID.lastError  = sArmPID.error;
	return ( (sArmPID.error * sArmPID.kP) + (sArmPID.derivative * sArmPID.kD) );
}








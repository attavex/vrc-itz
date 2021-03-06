#include "main.h"

// Joy Values
#define joyAxis1 joystickGetAnalog(1, 1)
#define joyAxis2 joystickGetAnalog(1, 2)
#define joyAxis3 joystickGetAnalog(1, 3)
#define joyAxis4 joystickGetAnalog(1, 4)
// Btn Values
#define bBtn7L joystickGetDigital(1, 7, JOY_LEFT)
#define bBtn7R joystickGetDigital(1, 7, JOY_RIGHT)
#define bBtn7U joystickGetDigital(1, 7, JOY_UP)
#define bBtn7D joystickGetDigital(1, 7, JOY_DOWN)
#define bBtn8L joystickGetDigital(1, 8, JOY_LEFT)
#define bBtn8R joystickGetDigital(1, 8, JOY_RIGHT)
#define bBtn8U joystickGetDigital(1, 8, JOY_UP)
#define bBtn8D joystickGetDigital(1, 8, JOY_DOWN)
#define bBtn5U joystickGetDigital(1, 5, JOY_UP)
#define bBtn5D joystickGetDigital(1, 5, JOY_DOWN)
#define bBtn6U joystickGetDigital(1, 6, JOY_UP)
#define bBtn6D joystickGetDigital(1, 6, JOY_DOWN)

inline void driveControl(int speed, int turn) //Arcade
{
    motorSet(DRIVE_LB, -speed - turn);
	motorSet(DRIVE_LF, speed + turn);
    motorSet(DRIVE_RB, -speed + turn);
	motorSet(DRIVE_RF, -speed + turn);
}

int mogoOutput;
inline void mogoControl(bool bBtnUp, bool bBtnDown)
{
	
    if(bBtnUp)      
	{
		mogoOutput = 127;  
	}
	else if (bBtnDown) 
	{
		mogoOutput = -127;
	}
	else if (analogRead(MOGO_POT) > 1200)
	{
		mogoOutput = 40;
	}
	else if (analogRead(MOGO_POT) < 75)
	{
		mogoOutput = -15;
	}
	else
	{
        mogoOutput = 0;
	}
	mogo(mogoOutput);
}

int liftOutput;	
int iArmDes = 325;
//iArmDes = 200;
inline void liftControl(bool bBtnUp, bool bBtnDown)
{
    if(bBtnUp || bBtnDown)
    {
        liftOutput = bBtnUp ? 127 : (bBtnDown ? -127 : 0);
        iArmDes = analogRead(LIFT_POT);
    } /*
	else if(analogRead(LIFT_POT) < 3500) 
	{
		liftOutput = -15;
	} */
    else
    {
        liftOutput = iArmPID(iArmDes);
    }

    lift(liftOutput);
}

int maniOutput;
inline void maniControl(bool bBtnUp, bool bBtnDown)
{
    if(bBtnUp)
	{
		maniOutput = (3800 - analogRead(MANI_POT))/6.25;                         
       // maniOutput = 90;
    }
	else if (bBtnDown)
	{
		maniOutput = -127;
	}
	else if(analogRead(MANI_POT) > 3400)
	{
		maniOutput = 15;
	}
	else if (analogRead(MANI_POT < 2200)) 
	{
        maniOutput = -15;
	}
	else
	{
        maniOutput = 0;
	}

	
	mani(maniOutput);
}

int rollerOutput;
inline void rollerControl(bool bBtnUp, bool bBtnDown, bool bBtnStop)
{
    if(bBtnUp)
	{
		rollerOutput = 127;
	}       
	else if (bBtnDown)
	{
		rollerOutput = -127;
	}
	else if (bBtnStop)
	{
		rollerOutput = 0;
	}
	else if(analogRead(MANI_POT) < 3200 && analogRead(LIFT_POT) < 200) {
		rollerOutput = 127;
	}
	else
	{	

        rollerOutput = 25;
	}
	roller(rollerOutput);
}

bool baseLockOutput = 0;
inline void baseLock(bool enableLock, bool disableLock, int speed, int turn)
{
	if(enableLock)
	{
		baseLockOutput = 1;
	}
	else if(disableLock)
	{
		baseLockOutput = 0;
	}

	if(baseLockOutput == 1)
	{
	    motorSet(DRIVE_LB, -40);
	    motorSet(DRIVE_LF, -30);
        motorSet(DRIVE_RB, 40);
	    motorSet(DRIVE_RF, -30); 
	}
	else if(baseLockOutput == 1 && (joystickGetAnalog(1, joyAxis3) == 1 || joystickGetAnalog(1, joyAxis4) == 1))
	{
		baseLockOutput = 0;
	}
	else if(baseLockOutput == 0)
	{
        motorSet(DRIVE_LB, -speed - turn);
	    motorSet(DRIVE_LF, speed + turn);
        motorSet(DRIVE_RB, -speed + turn);
	    motorSet(DRIVE_RF, -speed + turn);
	}
}

void operatorControl() {
	encoderReset(LEFT_ENCODER);
	encoderReset(RIGHT_ENCODER);
	while (true) 
	{
     delay(20);
	 lcdClear(uart1); 
	 lcdPrint(uart1, 1, "Batt: %1.3f V", (double)powerLevelMain() / 1000);
	 lcdPrint(uart1, 2, "Batt: %1.3f V", (double)analogRead(POWER_EXP) / 280);
	//lcdPrint(uart1, 1, "MANI - %d", analogRead(MANI_POT));
	//lcdPrint(uart1, 2, "LIFT - %d", analogRead(LIFT_POT));
	//driveControl(joyAxis3, joyAxis4);
	mogoControl(bBtn8L, bBtn8U);
	liftControl(bBtn6U, bBtn6D);
	maniControl(bBtn5U, bBtn5D);
	rollerControl(bBtn8R, bBtn7L, bBtn8D);
	baseLock(bBtn7R, bBtn7D, joyAxis3, joyAxis4); 
	printf("%d %d %d\n", analogRead(MOGO_POT), analogRead(LIFT_POT), analogRead(MANI_POT));
	}
}
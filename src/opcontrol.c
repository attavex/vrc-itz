/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
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
	else
	{
        mogoOutput = 0;
	}
	
	mogo(mogoOutput);
}

int liftOutput;
inline void liftControl(bool bBtnUp, bool bBtnDown)
{
    if(bBtnUp)
	{
		liftOutput = 127;
	}       
	else if (bBtnDown)
	{
		liftOutput = -127;
	}
	else if (analogRead(LIFT_POT) > 3500)
	{
		liftOutput = -10;
	}
	else
	{
		liftOutput = 10;
	}

	lift(liftOutput);
}

int maniOutput;
inline void maniControl(bool bBtnUp, bool bBtnDown)
{
    if(bBtnUp)
	{
		maniOutput = 120;
	}       
	else if (bBtnDown)
	{
		maniOutput = -110;
	}
	else
	{
        maniOutput = 8;
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
	else
	{
        rollerOutput = 25;
	}
	roller(rollerOutput);
}


void operatorControl() {
	while (true) {
     delay(20);
	driveControl(joyAxis3, joyAxis4);
	mogoControl(bBtn8L, bBtn8U);
	liftControl(bBtn6U, bBtn6D);
	maniControl(bBtn5U, bBtn5D);
	rollerControl(bBtn8R, bBtn7L, bBtn8D);
	printf("%d\n", analogRead(LIFT_POT));
		
	}
}
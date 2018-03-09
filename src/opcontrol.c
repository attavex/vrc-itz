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
inline void driveControl(int speed, int turn) //Arcade
{
    motorSet(DRIVE_L1, speed + turn);
    motorSet(DRIVE_L2, speed + turn);
    motorSet(DRIVE_R1, speed + turn);
    motorSet(DRIVE_R2, speed + turn);
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
	else if (analogRead(ARM_SENSOR) > 500)
	{
		liftOutput = 15;
	}
	else
	{
		liftOutput = -5;
	}
	lift(liftOutput);

    

}

void operatorControl() {
	while (true) {
     delay(20);
	driveControl(joystickGetAnalog(1, 2), joystickGetAnalog(1,4));
	
		
	}
}
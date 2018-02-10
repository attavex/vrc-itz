#pragma config(Motor,  port2,           Mani,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           DriveR,        tmotorVex393HighSpeed_MC29, openLoop, reversed, driveLeft, encoderPort, dgtl1)
#pragma config(Motor,  port4,           LY1,           tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LMOGO,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Intake,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           DriveL,        tmotorVex393HighSpeed_MC29, openLoop, driveRight, encoderPort, dgtl3)
#pragma config(Motor,  port8,           LY2,           tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           RMOGO,         tmotorVex393_MC29, openLoop)


int R_FREQ = 100; // 100 the frequency of the recording in milisecons. A lower number will attempt to capture more data, but may result in errors in the recording
int R_Batt; // the battery voltage at the time of the recording.
int P_Freq; // the replay frequency in miliseconds
int lineCounter = 0; // the number of each line of recorded code
int timeCounter = 0 * R_FREQ; // the time in mS of each line
int C1, C2, C3, C4, B5D, B5U, B6D, B6U, B7D, B7L, B7R, B7U, B8D, B8L, B8R, B8U; // signal values from main controller
int xC1, xC2, xC3, xC4, xB5D, xB5U, xB6D, xB6U, xB7D, xB7L, xB7R, xB7U, xB8D, xB8L, xB8R, xB8U; // signal values from partner controller



// function to assess battery voltage and adjust replay frequency
void replayFreq()
{
	P_Freq = R_FREQ * (R_Batt / nImmediateBatteryLevel);	//  with R_FREQ at 100, there would be ~1mS difference in playback per 80mV difference in voltage
	// recording at 8200mV and playback at 7200mV would make P_Freq = 113mS, meaning the last ~2 secs would be stopped by competition control
	// what is the real relationship of voltage and speed?  would vary greatly by robot weight and geomoetry.  Add a constant for teams to tune?
}

// function to record main controller channel signals to globals
void main_C(int C1_now, int C2_now, int C3_now, int C4_now)
{
	C1 = C1_now;
	C2 = C2_now;
	C3 = C3_now;
	C4 = C4_now;
}

// function to record main controller button signals to globals
void main_B(int B5D_now, int B5U_now, int B6D_now, int B6U_now, int B7D_now, int B7L_now, int B7R_now, int B7U_now, int B8D_now, int B8L_now, int B8R_now, int B8U_now)
{
	B5D = B5D_now;
	B5U = B5U_now;
	B6D = B6D_now;
	B6U = B6U_now;
	B7D = B7D_now;
	B7L = B7L_now;
	B7R = B7R_now;
	B7U = B7U_now;
	B8D = B8D_now;
	B8L = B8L_now;
	B8R = B8R_now;
	B8U = B8U_now;
}

// function to record partner controller channel signals to globals
void partner_C(int xC1_now, int xC2_now, int xC3_now, int xC4_now)
{
	xC1 = xC1_now;
	xC2 = xC2_now;
	xC3 = xC3_now;
	xC4 = xC4_now;
}

// function to record partner controller button signals to globals
void partner_B(int xB5D_now, int xB5U_now, int xB6D_now, int xB6U_now, int xB7D_now, int xB7L_now, int xB7R_now, int xB7U_now, int xB8D_now, int xB8L_now, int xB8R_now, int xB8U_now)
{
	xB5D = xB5D_now;
	xB5U = xB5U_now;
	xB6D = xB6D_now;
	xB6U = xB6U_now;
	xB7D = xB7D_now;
	xB7L = xB7L_now;
	xB7R = xB7R_now;
	xB7U = xB7U_now;
	xB8D = xB8D_now;
	xB8L = xB8L_now;
	xB8R = xB8R_now;
	xB8U = xB8U_now;
}


// function to set motor values to recorded signals
void replayVexRT()
{
	//Drive
	tankControl(C2,C3);




	//MOGO Intake (2nd Controller)
	if (xB6U == 1){
		motor[LMOGO] = 127;
		motor[RMOGO] = -127;
	}
	else if (xB6D == 1){
		motor[LMOGO] = -127;
		motor[RMOGO] = 127;
	}
	else if (B7R == 1){ //main
		motor[LMOGO] = 127;
		motor[RMOGO] = -127;
	}
	else if (B8L == 1){
		motor[LMOGO] = -127;
		motor[RMOGO] = 127;
	}
	else
	{
		motor[LMOGO] = 0;
		motor[RMOGO] = 0;
	}


	//Lift(Main Controller)
	if (B6U == 1){
		motor[LY1] = 127;
		motor[LY2] = -127;
	}
	else if (B6D == 1){
		motor[LY1] = -127;
		motor[LY2] = 127;
	}
	else
	{
		motor[LY1] = 0;
		motor[LY2] = 0;
	}

	//Mani(Main Controller)
	if (B5U == 1){
		motor[Mani] = -115;
	}
	else if (B5D == 1){
		motor[Mani] = 115;
	}
	else
	{
		motor[Mani] = 0;
	}


	//intake

	if (B7L == 1){
		motor[Intake] = -127;
	}
	else if (B8R == 1){
		motor[Intake] = 127;
	}
	else {
		motor[Intake] = 27;
	}

	wait1Msec(P_Freq);
}
/*-----------------------------------------------------------------------------------END COPY-------*/


// task to record vexRT signals to the debug stream once every R_FREQ ms
task recordVexRT()
{
	while(true)
	{
		// main controller values
		C1 = vexRT[Ch1];
		C2 = vexRT[Ch2];
		C3 = vexRT[Ch3];
		C4 = vexRT[Ch4];
		B5D = vexRT[Btn5D];
		B5U = vexRT[Btn5U];
		B6D = vexRT[Btn6D];
		B6U = vexRT[Btn6U];
		B7D = vexRT[Btn7D];
		B7L = vexRT[Btn7L];
		B7R = vexRT[Btn7R];
		B7U = vexRT[Btn7U];
		B8D = vexRT[Btn8D];
		B8L = vexRT[Btn8L];
		B8R = vexRT[Btn8R];
		B8U = vexRT[Btn8U];

		// partner controller values
		xC1 = vexRT[Ch1Xmtr2];
		xC2 = vexRT[Ch2Xmtr2];
		xC3 = vexRT[Ch3Xmtr2];
		xC4 = vexRT[Ch4Xmtr2];
		xB5D = vexRT[Btn5DXmtr2];
		xB5U = vexRT[Btn5UXmtr2];
		xB6D = vexRT[Btn6DXmtr2];
		xB6U = vexRT[Btn6UXmtr2];
		xB7D = vexRT[Btn7DXmtr2];
		xB7L = vexRT[Btn7LXmtr2];
		xB7R = vexRT[Btn7RXmtr2];
		xB7U = vexRT[Btn7UXmtr2];
		xB8D = vexRT[Btn8DXmtr2];
		xB8L = vexRT[Btn8LXmtr2];
		xB8R = vexRT[Btn8RXmtr2];
		xB8U = vexRT[Btn8UXmtr2];

		// increment lineCounter and timeCounter
		lineCounter++;
		timeCounter = lineCounter * R_FREQ;

		// write the values from the  main controller to the debug stream window
		writeDebugStream("main_C(%d", C1);
		writeDebugStream(",%d", C2);
		writeDebugStream(",%d", C3);
		writeDebugStream(",%d", C4); // break signals into channel and button groups
		writeDebugStream("); main_B(%d", B5D);
		writeDebugStream(",%d", B5U);
		writeDebugStream(",%d", B6D);
		writeDebugStream(",%d", B6U);
		writeDebugStream(",%d", B7D);
		writeDebugStream(",%d", B7L);
		writeDebugStream(",%d", B7R);
		writeDebugStream(",%d", B7U);
		writeDebugStream(",%d", B8D);
		writeDebugStream(",%d", B8L);
		writeDebugStream(",%d", B8R);
		writeDebugStream(",%d", B8U);
		writeDebugStream(");  ");

		// write the values from the partner controller to the debug stream window
		writeDebugStream("partner_C(%d", xC1);
		writeDebugStream(",%d", xC2);
		writeDebugStream(",%d", xC3);
		writeDebugStream(",%d", xC4);
		writeDebugStream("); partner_B(%d", xB5D);
		writeDebugStream(",%d", xB5U);
		writeDebugStream(",%d", xB6D);
		writeDebugStream(",%d", xB6U);
		writeDebugStream(",%d", xB7D);
		writeDebugStream(",%d", xB7L);
		writeDebugStream(",%d", xB7R);
		writeDebugStream(",%d", xB7U);
		writeDebugStream(",%d", xB8D);
		writeDebugStream(",%d", xB8L);
		writeDebugStream(",%d", xB8R);
		writeDebugStream(",%d", xB8U);
		writeDebugStream(");  ");

		writeDebugStreamLine("replayVexRT(); // %d", timeCounter);

		wait1Msec(R_FREQ);

	}
}

task main()
{
	// clear previous recordings
	clearDebugStream();
	wait1Msec(100);
	// save current battery voltage to R_Batt
	R_Batt = nImmediateBatteryLevel;

	// countdown in debug stream
	writeDebugStreamLine("// Begin recording in: 3");
	wait1Msec(1000);
	writeDebugStreamLine("// Begin recording in: 2");
	wait1Msec(1000);
	writeDebugStreamLine("// Begin recording in: 1");
	wait1Msec(1000);

	// write header for autonomous code
	writeDebugStreamLine("// BEGIN AUTONOMOUS RECORDING");
	writeDebugStreamLine("// Copy the following lines into your autonomous task:");
	writeDebugStreamLine("// R_FREQ = %d", R_FREQ);
	writeDebugStream("R_Batt = %d", R_Batt);
	writeDebugStreamLine(";");
	writeDebugStreamLine("replayFreq();");

	// start recording the vexRT signals
	startTask (recordVexRT);

	// allow driver control for 15 seconds
	clearTimer(T1);
	while (time1[T1] < 15000)
	{

		tankControl(Ch2,Ch3);

		//MOGO Intake (2nd Controller)
		if (vexRT[Btn6UXmtr2] == 1){
			motor[LMOGO] = 127;
			motor[RMOGO] = -127;
		}
		else if (vexRT[Btn6DXmtr2] == 1){
			motor[LMOGO] = -127;
			motor[RMOGO] = 127;
		}
		else if (vexRT[Btn7R] == 1){ //main
			motor[LMOGO] = 127;
			motor[RMOGO] = -127;
		}
		else if (vexRT[Btn8L] == 1){
			motor[LMOGO] = -127;
			motor[RMOGO] = 127;
		}
		else
		{
			motor[LMOGO] = 0;
			motor[RMOGO] = 0;
		}


		//Lift(Main Controller)
		if (vexRT[Btn6U] == 1){
			motor[LY1] = 127;
			motor[LY2] = -127;
		}
		else if (vexRT[Btn6D] == 1){
			motor[LY1] = -127;
			motor[LY2] = 127;
		}
		else
		{
			motor[LY1] = 0;
			motor[LY2] = 0;
		}

		//Mani(Main Controller)
		if (vexRT[Btn5U] == 1){
			motor[Mani] = -115;
		}
		else if (vexRT[Btn5D] == 1){
			motor[Mani] = 115;
		}
		else
		{
			motor[Mani] = 0;
		}


		//intake

		if (vexRT[Btn7L] == 1){
			motor[Intake] = -127;
		}
		else if (vexRT[Btn8R] == 1){
			motor[Intake] = 127;
		}
		else {
			motor[Intake] = 27;
		}

	}

	// stop recording the vexRT signals
	stopTask (recordVexRT);
	writeDebugStreamLine("motor[port1] = motor[port2] = motor[port3] = motor[port4] = motor[port5] = motor[port6] = motor[port7] = motor[port8] = motor[port9] = motor[port10] = 0;");
	writeDebugStreamLine("// END AUTON RECORDING");

	// stop all motors
	motor[port1] = motor[port2] = motor[port3] = motor[port4] = motor[port5] = motor[port6] = motor[port7] = motor[port8] = motor[port9] = motor[port10] = 0;
}

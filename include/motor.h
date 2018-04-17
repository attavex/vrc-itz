#include "API.h"


/* ------------------------------Motor Numbers--------------------------------- */
#define DRIVE_RB 1
#define DRIVE_RF 2
#define R_LIFT   3
#define R_MANI 4
#define MOGO  5
#define INTAKE   6
#define L_MANI   7
#define L_LIFT 8
#define DRIVE_LF 9
#define DRIVE_LB 10



/* ------------------------------Analog Sensors--------------------------------- */
#define MOGO_POT 1
#define LIFT_POT 2
#define MANI_POT 3
#define GYRO_PORT 4

Gyro GYRO;

// Bat Voltage (Power Exp)
#define POWER_EXP 4


/*-----------------------------Digital Sensors---------------------------------- */
#define RIGHT_QUAD_TOP_PORT 1
#define RIGHT_QUAD_BOTTOM_PORT 2
#define LEFT_QUAD_TOP_PORT 3
#define LEFT_QUAD_BOTTOM_PORT 4

Encoder RIGHT_ENCODER;
Encoder LEFT_ENCODER;


// PID //
typedef struct {
    float current;
    float kP;
    float kI;
    float kD;
    float target;
    float integral;
    float error;
    float derivative;
    float lastError;
} pid;

//Lift
int iArmPID(int iDes);
//Drive
int iDrivePID(int iDes);

// ~~~DEFINE ALL FUNCTIONS~~~ //
void driveSpeed(int iSpeed);
void lift(int iSpeed);
void mogo(int iSpeed);
void roller(int iSpeed);
void mani(int iSpeed);
void pidDrive(void * parameter);
void pidRotate(void * parameter);
void lcdAuton_Pages(int selectVal);
void lcdAuton();
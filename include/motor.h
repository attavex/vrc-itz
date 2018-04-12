#include "API.h"


/* -------------------------------Motor Numbers--------------------------------- */
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

int iArmPID(int iDes);



void lift(int iSpeed);
void mogo(int iSpeed);
void roller(int iSpeed);
void mani(int iSpeed);
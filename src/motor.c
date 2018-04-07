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










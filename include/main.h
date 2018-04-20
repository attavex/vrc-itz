#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>
#include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

int selectAuton[3];

void autonomous();
void initializeIO(); 
void initialize();
void operatorControl();

#ifdef __cplusplus
}
#endif

#endif

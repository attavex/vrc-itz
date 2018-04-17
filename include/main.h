#ifndef MAIN_H_

// This prevents multiple inclusion, which isn't bad for this file but is good practice
#define MAIN_H_

#include <API.h>
#include "motor.h"

// Allow usage of this file in C++ programs
#ifdef __cplusplus
extern "C" {
#endif

int selectAuton[3];

void autonomous();
void initializeIO(); 
void initialize();
void operatorControl();

// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif

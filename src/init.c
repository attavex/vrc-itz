
#include "main.h"

void initialize() {
  //LCD Inits
  lcdInit(uart1);
  lcdSetBacklight(uart1, 1);

  //Sensor Inits
  RIGHT_ENCODER = encoderInit(RIGHT_QUAD_TOP_PORT, RIGHT_QUAD_BOTTOM_PORT, true);
  LEFT_ENCODER = encoderInit(LEFT_QUAD_TOP_PORT, LEFT_QUAD_BOTTOM_PORT, false);
  GYRO = gyroInit(GYRO_PORT, 0);
  

  //Auton Choice
  if(!isEnabled())
  {
    lcdAuton();
  }
  

  
}


#include "main.h"

inline void driveForward(int ticks, int speed)
{
  while(encoderGet(LEFT_ENCODER) < ticks)
      {
        motorSet(DRIVE_LB, -speed);
	      motorSet(DRIVE_LF, -speed);
        motorSet(DRIVE_RB, speed);
	      motorSet(DRIVE_RF, -speed);
      }

}
inline void mogoDown()
{
  while(analogRead(MOGO_POT) < 1200)
  {
    mogo(127);
  }
  while(analogRead(MOGO_POT) > 1110)
  {
    mogo(30);
  }
  mogo(0);
}

inline void maniLiftDown()
{

}



void mogoAutonMaster20(int choice)
{
    if(choice == 1)
    {
      encoderReset(LEFT_ENCODER);
      mogoDown();
      driveForward(800, 127);
     
      
        //insert red-side, 20 point, 2 cone auton
    }
    else if(choice == 2)
    {
        //insert blue-side, 20 point, 2 cone auton
    }
    else if(choice == 3)
    {
        //insert red-side, 20 point, 3 cone auton
    }
    else if(choice == 4)
    {
        //insert blue-side, 20 point, 3 cone auton
    }
}

void mogoAutonMaster5(int choice)
{
    if(choice == 1)
    {
        //insert red-side, 5 point, 2 cone auton
    }
    else if(choice == 2)
    {
        //insert blue-side, 5 point, 2 cone auton
    }
    else if(choice == 3)
    {
        //insert red-side, 5 point, 3 cone auton
    }
    else if(choice == 4)
    {
        //insert blue-side, 5 point, 3 cone auton
    }
}

void stationaryAuton()
{
    //insert stationary 3 cone auton
}

void progSkills()
{
    //insert prog skills 
}










void autonomous() 
{

  //20pt mogo
  if (selectAuton[0] == 1)
  {
    //two cones
    if (selectAuton[1] == 1)
    {
      //red side
      if (selectAuton[2] == 1)
      {
        mogoAutonMaster20(1);
      }
      //blue side
      if (selectAuton[2] == 2)
      {
        mogoAutonMaster20(2);
      }
    }
    //three cones
    if (selectAuton[1] == 2)
    {
      //red side
      if (selectAuton[2] == 1)
      {
        mogoAutonMaster20(3);
      }
      //blue side
      if (selectAuton[2] == 2)
      {
        mogoAutonMaster20(4);
      }
    }
  }


  //5pt mogo
  if (selectAuton[0] == 2)
  {
    //two cone
    if (selectAuton[1] == 1)
    {
      //red side
      if (selectAuton[2] == 1)
      {
        mogoAutonMaster5(1);

      }
      //blue side
      if (selectAuton[2] == 2)
      {
        mogoAutonMaster5(2);
      }
    }
    //three cones
    if (selectAuton[1] == 2)
    {
      //red side
      if (selectAuton[2] == 1)
      {
        mogoAutonMaster5(3);
      }
      //blue side
      if (selectAuton[2] == 2)
      {
        mogoAutonMaster5(4);
      }
    }
  }

  //stationary
  if (selectAuton[0] == 3)
  {
      stationaryAuton();
  }
  //programming skills
  if (selectAuton[0] == 4)
  {
   progSkills();
  }
}
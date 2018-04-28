#include "main.h"

TaskHandle driveTask, turnTask;






void testPIDRotate(int gyDes)
{
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
//anything here will run
  while(gyroGet(GYRO) < gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
}

void testPIDDrive(int dDes)
{
  driveTask = taskCreate(pidDrive, TASK_DEFAULT_STACK_SIZE, (void*)dDes, TASK_PRIORITY_DEFAULT);
 //anything here will run
  while(driveGet() < dDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(driveTask);
}

int dDes;
int gyDes;
void mogoAutonMaster20(int choice) 
{
    if(choice == 1)
    {
        //insert dominant(less cones(match loader))-side, 20 point, 2 cone auton
              roller(20);
    mogo(127);
    lift(127);
    while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1700) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1730) mogo(20);
    delay(20);
  }
    
    driveSpeed(127);
  while(driveGet() < 1220) 
  {  
    if(driveGet() > 1220) driveSpeed(5);
    delay(20);
  }
  driveSpeed(0);
  //motorStopAll();
  wait(200);
  mogo(-127);
   while (analogRead(MOGO_POT) > 100)
  {
  if(analogRead(MOGO_POT) < 90)
  {
    mogo(-5); 
  }  
  delay(20);
  }
  
  lift(-127);
   while(analogRead(LIFT_POT) > 100) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);//PRELOAD CONE DROPS ONTO MOGO
  //start of picking-up second cone
    encoderReset(LEFT_ENCODER);
    encoderReset(RIGHT_ENCODER);
    lift(127);
     while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
    driveSpeed(127);
  while(driveGet() < 136) 
  {  
    if(driveGet() > 136) driveSpeed(0);
    delay(20);
  }
  driveSpeed(0);
  motorStopAll();
  lift(-80);
  mani(-127);
  roller(127);
  while(analogRead(LIFT_POT) > 10 || analogRead(MANI_POT) > 2800) 
  {  
    if(analogRead(LIFT_POT) < 10) lift(-10);
    if(analogRead(MANI_POT) < 2800) mani(-10);
    delay(20);
  }
  wait(250);
  //BRING UP MANI AND STACK SECOND CONE
  mani(127);
  lift(127);
   while(analogRead(MANI_POT) < 3450 || analogRead(LIFT_POT) < 125)
  {
  if(analogRead(MANI_POT) > 3480)
  {
    mani(0);
    
  } 
  if(analogRead(LIFT_POT) > 125) lift(10);
  delay(20);
  }
   lift(-127);
   while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);
  driveSpeed(-127);
   while(driveGet() > -1275)
  {
  if(driveGet() < -1275) driveSpeed(0); 
  delay(20);
  }
  //FIRST TURN TO LINE UP PARALLEL WITH SCORING BAR
  gyDes = -135;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) > gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  //CENTER ON BAR (STILL PARALLEL)
  encoderReset(LEFT_ENCODER);
  encoderReset(RIGHT_ENCODER);
 driveSpeed(127);
   while(driveGet() < 225)
  {
  if(driveGet() > 225) driveSpeed(0); 
  delay(20);
  }
  //PERPINDICULAR TO BAR
  gyDes = -225;
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) > gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  motorStopAll();
  //INSERT MOGO INTO 20 POINT ZONE
  driveSpeed(127);
  wait(750);
  roller(-127);
  lift(127);
  mogo(127);
  while(analogRead(LIFT_POT) > 300 || analogRead(MOGO_POT) < 1400) 
  {  
    if(analogRead(LIFT_POT) < 300) lift(10);
    if(analogRead(MOGO_POT) > 1400)
    {
      mogo(20); 
    }
    delay(20);
  }
  wait(1000);
  driveSpeed(0);
  //BACK UP AND END AUTON
  mogo(-127);
  driveSpeed(-127);
  while(analogRead(MOGO_POT) > 500)
  {
  if(analogRead(MOGO_POT) < 200)
  {
     mogo(0); 
     driveSpeed(0);
  }
  delay(20);
  }
    }
    else if(choice == 2)
    {
        //insert recessive(more cones)-side, 20 point, 2 cone auton
             roller(20);
    mogo(127);
    lift(127);
    while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1700) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1730) mogo(20);
    delay(20);
  }
    
    driveSpeed(127);
  while(driveGet() < 1220) 
  {  
    if(driveGet() > 1220) driveSpeed(5);
    delay(20);
  }
  driveSpeed(0);
  //motorStopAll();
  wait(200);
  mogo(-127);
   while (analogRead(MOGO_POT) > 100)
  {
  if(analogRead(MOGO_POT) < 90)
  {
    mogo(-5); 
  }  
  delay(20);
  }
  
  lift(-127);
   while(analogRead(LIFT_POT) > 100) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);//PRELOAD CONE DROPS ONTO MOGO
  //start of picking-up second cone
    encoderReset(LEFT_ENCODER);
    encoderReset(RIGHT_ENCODER);
    lift(127);
     while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
    driveSpeed(127);
  while(driveGet() < 136) 
  {  
    if(driveGet() > 136) driveSpeed(0);
    delay(20);
  }
  driveSpeed(0);
  motorStopAll();
  lift(-80);
  mani(-127);
  roller(127);
  while(analogRead(LIFT_POT) > 10 || analogRead(MANI_POT) > 2800) 
  {  
    if(analogRead(LIFT_POT) < 10) lift(-10);
    if(analogRead(MANI_POT) < 2800) mani(-10);
    delay(20);
  }
  wait(250);
  //BRING UP MANI AND STACK SECOND CONE
  mani(127);
  lift(127);
   while(analogRead(MANI_POT) < 3450 || analogRead(LIFT_POT) < 125)
  {
  if(analogRead(MANI_POT) > 3480)
  {
    mani(0);
    
  } 
  if(analogRead(LIFT_POT) > 125) lift(10);
  delay(20);
  }
   lift(-127);
   while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);
  driveSpeed(-127);
  roller(26);
   while(driveGet() > -1275)
  {
  if(driveGet() < -1275) driveSpeed(0); 
  delay(20);
  }
  //FIRST TURN TO LINE UP PARALLEL WITH SCORING BAR
  gyDes = 135;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) < gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  //CENTER ON BAR (STILL PARALLEL)
  encoderReset(LEFT_ENCODER);
  encoderReset(RIGHT_ENCODER);
 driveSpeed(127);
   while(driveGet() < 225)
  {
  if(driveGet() > 225) driveSpeed(0); 
  delay(20);
  }
  //PERPINDICULAR TO BAR
  gyDes = 225;
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) < gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  motorStopAll();
  //INSERT MOGO INTO 20 POINT ZONE
  driveSpeed(127);
  wait(750);
  roller(-127);
  lift(127);
  mogo(127);
  while(analogRead(LIFT_POT) < 300 || analogRead(MOGO_POT) < 1400) 
  {  
    if(analogRead(LIFT_POT) > 300) lift(10);
    if(analogRead(MOGO_POT) > 1400)
    {
      mogo(20); 
    }
    delay(20);
  }
  wait(1000);
  driveSpeed(0);
  //BACK UP AND END AUTON
  mogo(-127);
  driveSpeed(-127);
  while(analogRead(MOGO_POT) > 500)
  {
  if(analogRead(MOGO_POT) < 200)
  {
     mogo(0); 
     driveSpeed(0);
  }
  delay(20);
  }
    }
}

void mogoAutonMaster5(int choice)
{
    if(choice == 1)
    {
        //insert dominant(less cones)-side, 5 point, 3 cone auton
              roller(20);
    mogo(127);
    lift(127);
    while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1700) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1730) mogo(20);
    delay(20);
  }
    
    driveSpeed(127);
  while(driveGet() < 1220) 
  {  
    if(driveGet() > 1220) driveSpeed(5);
    delay(20);
  }
  driveSpeed(0);
  //motorStopAll();
  wait(200);
  mogo(-127);
   while (analogRead(MOGO_POT) > 100)
  {
  if(analogRead(MOGO_POT) < 90)
  {
    mogo(-5); 
  }  
  delay(20);
  }
  
  lift(-127);
   while(analogRead(LIFT_POT) > 100) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);//PRELOAD CONE DROPS ONTO MOGO
  //start of picking-up second cone
    encoderReset(LEFT_ENCODER);
    encoderReset(RIGHT_ENCODER);
    lift(127);
     while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
    driveSpeed(127);
  while(driveGet() < 136) 
  {  
    if(driveGet() > 136) driveSpeed(0);
    delay(20);
  }
  driveSpeed(0);
  motorStopAll();
  lift(-80);
  mani(-127);
  roller(127);
  while(analogRead(LIFT_POT) > 10 || analogRead(MANI_POT) > 2800) 
  {  
    if(analogRead(LIFT_POT) < 10) lift(-10);
    if(analogRead(MANI_POT) < 2800) mani(-10);
    delay(20);
  }
  wait(250);
  //BRING UP MANI AND STACK SECOND CONE
  mani(127);
  lift(127);
   while(analogRead(MANI_POT) < 3450 || analogRead(LIFT_POT) < 125)
  {
  if(analogRead(MANI_POT) > 3480)
  {
    mani(0);
    
  } 
  if(analogRead(LIFT_POT) > 125) lift(10);
  delay(20);
  }
   lift(-127);
   while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);
  driveSpeed(-127);
   while(driveGet() > -1225)
  {
  if(driveGet() < -1225) driveSpeed(0); 
  delay(20);
  }
  //180° TURN TO INPUT MOGO IN ZONE
  gyDes = -180;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) > gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  roller(-127);
  lift(127);
  mogo(127);
  while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1400) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1400)
    {
      mogo(20); 
    }
    delay(20);
  }
  wait(100);
  driveSpeed(0);
  //BACK UP AND END AUTON
  driveSpeed(-127);
  wait(500);
  mogo(-127);
  
  while(analogRead(MOGO_POT) > 500)
  {
  if(analogRead(MOGO_POT) < 200)
  {
     mogo(0); 
     driveSpeed(0);
  }

    }
    }
    else if(choice == 2)
    {
         //insert recessive(more cones)-side, 5 point, 3 cone auton
          roller(20);
    mogo(127);
    lift(127);
    while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1700) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1730) mogo(20);
    delay(20);
  }
    
    driveSpeed(127);
  while(driveGet() < 1220) 
  {  
    if(driveGet() > 1220) driveSpeed(5);
    delay(20);
  }
  driveSpeed(0);
  //motorStopAll();
  wait(200);
  mogo(-127);
   while (analogRead(MOGO_POT) > 100)
  {
  if(analogRead(MOGO_POT) < 90)
  {
    mogo(-5); 
  }  
  delay(20);
  }
  
  lift(-127);
   while(analogRead(LIFT_POT) > 100) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);//PRELOAD CONE DROPS ONTO MOGO
  //start of picking-up second cone
    encoderReset(LEFT_ENCODER);
    encoderReset(RIGHT_ENCODER);
    lift(127);
     while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
    driveSpeed(127);
  while(driveGet() < 136) 
  {  
    if(driveGet() > 136) driveSpeed(0);
    delay(20);
  }
  driveSpeed(0);
  motorStopAll();
  lift(-80);
  mani(-127);
  roller(127);
  while(analogRead(LIFT_POT) > 10 || analogRead(MANI_POT) > 2800) 
  {  
    if(analogRead(LIFT_POT) < 10) lift(-10);
    if(analogRead(MANI_POT) < 2800) mani(-10);
    delay(20);
  }
  wait(250);
  //BRING UP MANI AND STACK SECOND CONE
  mani(127);
  lift(127);
   while(analogRead(MANI_POT) < 3450 || analogRead(LIFT_POT) < 125)
  {
  if(analogRead(MANI_POT) > 3480)
  {
    mani(0);
    
  } 
  if(analogRead(LIFT_POT) > 125) lift(10);
  delay(20);
  }
   lift(-127);
   while(analogRead(LIFT_POT) > 125) 
  {  
    if(analogRead(LIFT_POT) < 130) lift(10);
    delay(20);
  }
  roller(-127);
  driveSpeed(-127);
   while(driveGet() > -1225)
  {
  if(driveGet() < -1225) driveSpeed(0); 
  delay(20);
  }
  //180° TURN TO INPUT MOGO IN ZONE
  gyDes = 180;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) < gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  roller(-127);
  lift(127);
  mogo(127);
  while(analogRead(LIFT_POT) < 230 || analogRead(MOGO_POT) < 1400) 
  {  
    if(analogRead(LIFT_POT) > 250) lift(10);
    if(analogRead(MOGO_POT) > 1400)
    {
      mogo(20); 
    }
    delay(20);
  }
  wait(100);
  driveSpeed(0);
  //BACK UP AND END AUTON
  driveSpeed(-127);
  wait(500);
  mogo(-127);
  
  while(analogRead(MOGO_POT) > 500)
  {
  if(analogRead(MOGO_POT) < 200)
  {
     mogo(0); 
     driveSpeed(0);
  }

    }
}
}

void blockingAutonMaster(int choice)
{
  if (choice == 1)
  {
    gyDes = -20;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) > gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  wait(500);
  driveSpeed(127);
  while(driveGet() < 1225)
  {
  if(driveGet() > 1225) driveSpeed(0); 
  delay(20);
  }
  driveSpeed(0);
  }
  else if (choice == 2)
  {
    //other side blocking auton
      gyDes = 20;
  gyroReset(GYRO);
  turnTask = taskCreate(pidRotate, TASK_DEFAULT_STACK_SIZE, (void*)gyDes, TASK_PRIORITY_DEFAULT);
  while(gyroGet(GYRO) < gyDes)
  {
    delay(15);
  }
  delay(500);
  taskDelete(turnTask);
  driveSpeed(0);
  wait(300);
  driveSpeed(127);
  while(driveGet() < 1225)
  {
  if(driveGet() > 1225) driveSpeed(0); 
  delay(20);
  }
  driveSpeed(0);
  }
  }



void autonomous() 
{
  encoderReset(LEFT_ENCODER);
  encoderReset(RIGHT_ENCODER);
  gyroReset(GYRO);
  if(selectAuton[0] == 1) //20-point mogo 2 cone
  {
    if(selectAuton[2] == 1) //match loader side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      mogoAutonMaster20(1);
    }
    else if(selectAuton[2] == 2) //other side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      mogoAutonMaster20(2);
    }
  }

  if(selectAuton[0] == 2) //5-point mogo 2 cone
  {
     if(selectAuton[2] == 1) //Match loader side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      mogoAutonMaster5(1);
    }
    else if(selectAuton[2] == 2) //other side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      mogoAutonMaster5(2);
    }
  }

  if(selectAuton[0] == 3) //blocking
  {
       if(selectAuton[2] == 1) //Match loader side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      blockingAutonMaster(1);
    }
    else if(selectAuton[2] == 2) //other side
    {
      encoderReset(LEFT_ENCODER);
      encoderReset(RIGHT_ENCODER);
      gyroReset(GYRO);
      blockingAutonMaster(2);
    }
  }
  
}
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Nitheesh                                                  */
/*    Created:      11/5/2022, 6:58:59 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
vex::competition Competition;
// define your global instances of motors and other devices here
vex::motor RightFrontMotor = vex::motor(vex::PORT4);
vex::motor RightBackMotor = vex::motor(vex::PORT5);
vex::motor LeftFrontMotor = vex::motor(vex::PORT6);
vex::motor LeftBackMotor = vex::motor(vex::PORT7);
vex::motor intakeMotor = vex::motor(vex::PORT3);
vex::motor rollerMotor = vex::motor(vex::PORT2);
vex::motor shootingMotor = vex::motor(vex::PORT1);
vex::motor expansionMotor = vex::motor(vex::PORT9);
vex::controller Controller1 = vex::controller();
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
void intake(float time){
  intakeMotor.spin(forward, 100, percent);
  rollerMotor.spin(forward, 100, percent);
  wait(time, seconds);
  intakeMotor.stop();
  rollerMotor.stop();
}
void turnLeft(float time){
  // 1 second = 90 degrees
  LeftFrontMotor.spin(forward, -25, percent);
  LeftBackMotor.spin(forward, -25, percent);
  RightFrontMotor.spin(reverse, 25, percent);
  RightBackMotor.spin(reverse, 25, percent);
  wait(time, seconds);
  LeftFrontMotor.stop();
  LeftBackMotor.stop();
  RightFrontMotor.stop();
  RightBackMotor.stop();
}
void turnRight(float time){
  // 1 second = 90 degrees
  LeftBackMotor.spin(reverse, -25, percent);
  LeftFrontMotor.spin(reverse, -25, percent);
  RightBackMotor.spin(forward, 25, percent);
  RightFrontMotor.spin(forward, 25, percent);
  wait(time, seconds);
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}
void driveForward(float time){
  LeftBackMotor.spin(reverse, 25, percent);
  LeftFrontMotor.spin(reverse, 25, percent);
  RightBackMotor.spin(forward, 25, percent);
  RightFrontMotor.spin(forward, 25, percent);
  wait(time, seconds);
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}
void driveBackward(float time){
  LeftBackMotor.spin(forward, 25, percent);
  LeftFrontMotor.spin(forward, 25, percent);
  RightBackMotor.spin(reverse, 25, percent);
  RightFrontMotor.spin(reverse, 25, percent);
  wait(time, seconds);
  LeftBackMotor.stop();
  LeftFrontMotor.stop();
  RightBackMotor.stop();
  RightFrontMotor.stop();
}
void shooting(float time){
  shootingMotor.spin(forward, 100, percent);
  wait(time, seconds);
  shootingMotor.stop();
}
void roller(float time){
  rollerMotor.spin(reverse, 100, percent);
  wait(time, seconds);
  rollerMotor.stop();
}
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  driveBackward(2);
  roller(.25);
  driveForward(.2);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  LeftBackMotor.setStopping(brakeType::brake);
  LeftFrontMotor.setStopping(brakeType::brake);
  RightBackMotor.setStopping(brakeType::brake);
  RightFrontMotor.setStopping(brakeType::brake);
  intakeMotor.setStopping(brakeType::brake);
  rollerMotor.setStopping(brakeType::brake);
  shootingMotor.setStopping(brakeType::brake);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    
    //Left Motors
    int leftSpeed = Controller1.Axis3.value() + Controller1.Axis4.value();
    if (abs(leftSpeed) >= 110){
      leftSpeed = Controller1.Axis3.value() + Controller1.Axis4.value();
    }
    else{
      leftSpeed = (Controller1.Axis3.value() + Controller1.Axis4.value()) / 2;
    }
    LeftBackMotor.spin(directionType::fwd, leftSpeed, velocityUnits::pct);
    LeftFrontMotor.spin(directionType::fwd, leftSpeed, velocityUnits::pct);

    //Right Motors
    int RightSpeed = Controller1.Axis3.value() - Controller1.Axis4.value();
    if (abs(RightSpeed) >= 110){
      RightSpeed = Controller1.Axis3.value() - Controller1.Axis4.value();
    }
    else{
      RightSpeed = (Controller1.Axis3.value() - Controller1.Axis4.value()) / 2;
    }
    RightBackMotor.spin(directionType::rev, RightSpeed, velocityUnits::pct);
    RightFrontMotor.spin(directionType::rev, RightSpeed, velocityUnits::pct);

    // Intake
    if (Controller1.ButtonL2.pressing())
    {
      intakeMotor.spin(forward, 75, percent);
    }
    // Intake Reverse
    else if (Controller1.ButtonL1.pressing())
    {
      intakeMotor.spin(reverse, 75, percent);
    }
    else
    {
      intakeMotor.stop(brakeType::brake);
    }
    
    // Shooting
    if (Controller1.ButtonR2.pressing())
    {
      shootingMotor.spin(forward, 100, percent);
    }else if(Controller1.ButtonUp.pressing()){
      shootingMotor.spin(forward, 75, percent);
    }
    else if(Controller1.ButtonDown.pressing()){
      shootingMotor.spin(reverse,75,percent);
    }
    else
    {
      shootingMotor.stop(brakeType::brake);
    }

    if (Controller1.ButtonX.pressing())
    {
      rollerMotor.spin(forward, 75, percent);
    }
    else if(Controller1.ButtonB.pressing())
    {
      rollerMotor.spin(reverse, 75, percent);
    }else{
      rollerMotor.stop(brakeType::brake);
    }

    if(Controller1.ButtonLeft.pressing()){
      expansionMotor.spin(forward, 15, percent);
    }else if(Controller1.ButtonRight.pressing()){
      expansionMotor.spin(reverse, 15, percent);
    }else{
      expansionMotor.stop(brakeType::brake);
    }
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}

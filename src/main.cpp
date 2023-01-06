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
vex::motor LeftMotor = vex::motor(vex::PORT1);
vex::motor RightMotor = vex::motor(vex::PORT2);
vex::motor piston = vex::motor(vex::PORT4);
vex::motor intakeMotor = vex::motor(vex::PORT9);
vex::motor rollerMotor = vex::motor(vex::PORT19);
vex::motor shootingMotor = vex::motor(vex::PORT3);
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
  LeftMotor.spin(forward, -25, percent);
  RightMotor.spin(reverse, 25, percent);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
}
void turnRight(float time){
  // 1 second = 90 degrees
  LeftMotor.spin(reverse, -25, percent);
  RightMotor.spin(forward, 25, percent);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
}
void driveForward(float time){
  LeftMotor.spin(forward, 25, percent);
  RightMotor.spin(reverse, 25, percent);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
}
void driveBackward(float time){
  LeftMotor.spin(reverse, 100, percent);
  RightMotor.spin(forward, 100, percent);
  wait(time, seconds);
  LeftMotor.stop();
  RightMotor.stop();
}
void shooting(float time){
  shootingMotor.spin(reverse, 100, percent);
  wait(time, seconds);
  shootingMotor.stop();
}
void roller(float time){
  rollerMotor.spin(reverse, 100, percent);
  wait(time, seconds);
  rollerMotor.stop();
}
void usePiston(){
  piston.spin(forward, 100, percent);
  wait(0.3, seconds);
  piston.stop();
}
void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  driveBackward(2);
  roller(.25);
  driveForward(1);
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
  LeftMotor.setStopping(brakeType::brake);
  RightMotor.setStopping(brakeType::brake);
  intakeMotor.setStopping(brakeType::brake);
  rollerMotor.setStopping(brakeType::brake);
  shootingMotor.setStopping(brakeType::brake);
  piston.setStopping(brakeType::brake);
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
    leftSpeed = leftSpeed*2;
    LeftMotor.spin(directionType::rev, leftSpeed, velocityUnits::pct);

    //Right Motors
    int RightSpeed = Controller1.Axis3.value() - Controller1.Axis4.value();
    if (abs(RightSpeed) >= 110){
      RightSpeed = Controller1.Axis3.value() - Controller1.Axis4.value();
    }
    else{
      RightSpeed = (Controller1.Axis3.value() - Controller1.Axis4.value()) / 2;
    }
    RightSpeed = RightSpeed*2;
    RightMotor.spin(directionType::fwd, RightSpeed, velocityUnits::pct);

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
      shootingMotor.spin(reverse, 100, percent);
    }else if(Controller1.ButtonUp.pressing()){
      shootingMotor.spin(reverse, 75, percent);
    }
    else if(Controller1.ButtonDown.pressing()){
      shootingMotor.spin(forward,75,percent);
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

    if(Controller1.ButtonR1.pressing()){
      piston.spin(forward, 100, percent);
    }
    else if(Controller1.ButtonA.pressing()){
      usePiston();
    }
    else{
      piston.stop(brakeType::brake);
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

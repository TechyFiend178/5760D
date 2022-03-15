/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include <iostream>

// A global instance of competition
competition Competition;
motor intake = motor(PORT1, ratio18_1);
motor fleftdrive = motor(PORT17, ratio18_1);
motor frightdrive = motor(PORT16, ratio18_1, true);
motor shiftdrive = motor(PORT14, ratio36_1);
motor bleft = motor(PORT19, ratio18_1);
motor bright = motor(PORT18, ratio18_1,true);
motor rlift = motor(PORT12, ratio18_1, true);
motor llift = motor(PORT11, ratio18_1);
gps GPS1 = gps(PORT20, 6.875, -4.75, inches, 180);
//limit LimitSwitchA = vex::limit(Brain.ThreeWirePort.B);
//bumper Limitbutton = bumper(Brain.ThreeWirePort.A);
inertial Inert = inertial(PORT13);
distance mobiledist = distance(PORT9);
controller Controller1 = controller(primary);
distance dist2 = distance(PORT21);
optical Colorlimit = optical(PORT15);

// define your global instances of motors and other devices here
brain Brain;
limit LimitSwitchA = limit(Brain.ThreeWirePort.B);
bumper RLimitbutton = bumper(Brain.ThreeWirePort.A);
bumper LLimitbutton = bumper(Brain.ThreeWirePort.C);
motor_group Ldrive = motor_group(fleftdrive, bleft);
motor_group Rdrive = motor_group(frightdrive, bright);

float speedmod = 1;


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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  intake.resetRotation();
  shiftdrive.resetRotation();
  fleftdrive.resetRotation();
  frightdrive.resetRotation();
  bleft.resetRotation();
  bright.resetRotation();
  rlift.resetRotation();
  llift.resetRotation();
  GPS1.resetRotation();
  Inert.startCalibration();
  Inert.calibrate();
  Colorlimit.objectDetectThreshold();
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

void autonomous(void) {
  while(GPS1.xPosition()<0){
    fleftdrive.spin(directionType::rev, 50, percentUnits::pct);
    bleft.spin(directionType::rev, 50, percentUnits::pct);
    frightdrive.spin(directionType::rev, 50, percentUnits::pct);
    bright.spin(directionType::rev, 50, percentUnits::pct);
    if(!(RLimitbutton.pressing())){
      rlift.spin(directionType::fwd, 100, percentUnits::pct);
      }
    else{
      rlift.stop(brakeType::brake);
      rlift.setRotation(0, rotationUnits::deg);
    }
      if(!(LLimitbutton.pressing())){
      llift.spin(directionType::fwd, 100, percentUnits::pct);
      llift.setRotation(0, rotationUnits::deg);
      }
      else{
      rlift.stop(brakeType::brake);
    }
   // if(LimitSwitchA.pressing()){
    //  break;
    //}
  }
  fleftdrive.stop(brakeType::brake);
  frightdrive.stop(brakeType::brake);
  bleft.stop(brakeType::brake);
  bright.stop(brakeType::brake);
  rlift.spinFor(directionType::rev, 35*25, rotationUnits::deg, 50, velocityUnits::pct,false);
  llift.spinFor(directionType::rev, 35*25, rotationUnits::deg, 50, velocityUnits::pct);
 // while(!Colorlimit.{
  fleftdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bleft.spin(directionType::fwd, 70, percentUnits::pct);
    frightdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bright.spin(directionType::fwd, 70, percentUnits::pct);
  //}
    wait(1.5, timeUnits::sec);
 /*while(GPS1.xPosition()<1.2){
    fleftdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bleft.spin(directionType::fwd, 70, percentUnits::pct);
    frightdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bright.spin(directionType::fwd, 70, percentUnits::pct);
   }*/
   fleftdrive.stop(brakeType::brake);
  frightdrive.stop(brakeType::brake);
  bleft.stop(brakeType::brake);
  bright.stop(brakeType::brake);
  /* while(!(LLimitbutton.pressing() & !(RLimitbutton.pressing()))){
     if(!(RLimitbutton.pressing())){
      rlift.spin(directionType::fwd, 100, percentUnits::pct);
      }
    else{
      rlift.stop(brakeType::brake);
    }
      if(!(LLimitbutton.pressing())){
      llift.spin(directionType::fwd, 100, percentUnits::pct);
      }
      else{
      rlift.stop(brakeType::brake);
    }
   }*/
  rlift.rotateTo(0, rotationUnits::deg, 100, velocityUnits::pct, false);
  rlift.rotateTo(0, rotationUnits::deg, 100, velocityUnits::pct);
   fleftdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bleft.spin(directionType::fwd, 70, percentUnits::pct);
    frightdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bright.spin(directionType::fwd, 70, percentUnits::pct);
    wait(0.85, timeUnits::sec);
     fleftdrive.stop(brakeType::brake);
    frightdrive.stop(brakeType::brake);
   bleft.stop(brakeType::brake);
    bright.stop(brakeType::brake);
    while(dist2.objectDistance(distanceUnits::mm)>120){
      shiftdrive.spin(directionType::rev, 60, velocityUnits::pct);
    }
    shiftdrive.stop();
    while(!LimitSwitchA.pressing()){
    fleftdrive.spin(directionType::rev, 70, percentUnits::pct);
    bleft.spin(directionType::rev, 70, percentUnits::pct);
    frightdrive.spin(directionType::rev, 70, percentUnits::pct);
    bright.spin(directionType::rev, 70, percentUnits::pct);
}
     fleftdrive.stop(brakeType::brake);
    frightdrive.stop(brakeType::brake);
   bleft.stop(brakeType::brake);
    bright.stop(brakeType::brake);
    // rlift.spinFor(directionType::rev, 45*25, rotationUnits::deg, 50, velocityUnits::pct,false);
  //llift.spinFor(directionType::rev, 45*25, rotationUnits::deg, 50, velocityUnits::pct);
  while(mobiledist.objectDistance(distanceUnits::mm)<=110){
    rlift.spin(directionType::rev, 60, velocityUnits::pct);
    llift.spin(directionType::rev, 60, velocityUnits::pct);
  }
  intake.spin(directionType::fwd, 100, velocityUnits::pct);
  
  fleftdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bleft.spin(directionType::fwd, 70, percentUnits::pct);
    frightdrive.spin(directionType::fwd, 70, percentUnits::pct);
    bright.spin(directionType::fwd, 70, percentUnits::pct);
    
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

int points = 0;
void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    fleftdrive.spin(directionType::fwd, Controller1.Axis3.position()*speedmod, percentUnits::pct);
    bleft.spin(directionType::fwd, Controller1.Axis3.position()*speedmod, percentUnits::pct);
    frightdrive.spin(directionType::fwd, Controller1.Axis2.position()*speedmod, percentUnits::pct);
    bright.spin(directionType::fwd, Controller1.Axis2.position()*speedmod, percentUnits::pct);
    //Ldrive.spin(directionType::fwd, Controller1.Axis3.position(), percentUnits::pct);
    //Rdrive.spin(directionType::fwd, Controller1.Axis2.position(), percentUnits::pct);
    //bright.spin(directionType::fwd, 100, velocityUnits::pct);
    if(Controller1.ButtonL2.pressing()){
      if(!(RLimitbutton.pressing())){
      rlift.spin(directionType::fwd, 50, percentUnits::pct);
      }
      if(!(LLimitbutton.pressing())){
      llift.spin(directionType::fwd, 50, percentUnits::pct);
      }
    }
    else if(Controller1.ButtonL1.pressing()&(! (LimitSwitchA.pressing() & (mobiledist.objectDistance(distanceUnits::mm)<=110)))){
      rlift.spin(directionType::rev, 50, percentUnits::pct);
      llift.spin(directionType::rev, 50, percentUnits::pct);  
    }

  else{
      rlift.stop(brakeType::hold);
      llift.stop(brakeType::hold);
    }

    if(Controller1.ButtonRight.pressing()){
      shiftdrive.spin(directionType::rev, 50, percentUnits::pct);
    }
    else if(Controller1.ButtonY.pressing()){
      shiftdrive.spin(directionType::fwd, 50, percentUnits::pct);
    }
    else {
      shiftdrive.stop(brakeType::coast);
    }

    if(Controller1.ButtonR1.pressing()){
      intake.spin(directionType::fwd, 50, percentUnits::pct);
    }
    else if(Controller1.ButtonR2.pressing()){
      intake.spin(directionType::rev, 50, percentUnits::pct);
    }
    else {
      intake.stop(brakeType::brake);
    }
    
    if(Controller1.ButtonA.pressing()){
      std::cout << "\n Point: " << points;
      std::cout << "\n intake: " << intake.position(rotationUnits::deg);
      std::cout << "\n fleftdrive: " << fleftdrive.position(rotationUnits::deg);
      std::cout << "\n frightdrive: " << frightdrive.position(rotationUnits::deg);
      std::cout << "\n shiftdrive: " << shiftdrive.position(rotationUnits::deg);
      std::cout << "\n bleft: " << bleft.position(rotationUnits::deg);
      std::cout << "\n bright: " << bright.position(rotationUnits::deg);
      std::cout << "\n rlift: " << rlift.position(rotationUnits::deg);
      std::cout << "\n llift: " << llift.position(rotationUnits::deg);
      points++;
      wait(0.5, timeUnits::sec);
    }
    if(Controller1.ButtonB.pressing() & (speedmod == 1.0)){
      speedmod = 0.5;
      wait(0.5, timeUnits::sec);
    }
    else if(Controller1.ButtonB.pressing() & (speedmod == 0.5)){
      speedmod = 1.0;
      wait(0.5, timeUnits::sec);
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
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Robotics                                         */
/*    Created:      Fri Mar 18 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----

// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

#include <string>
using namespace std;
#include <iostream>
#include <list>
brain Brain;
motor testmot = motor(PORT11, ratio18_1);
motor testmot2 = motor(PORT12, ratio18_1, true);
motor testmot3 = motor(PORT13, ratio18_1);
motor testmot4 = motor(PORT14, ratio18_1, true);
motor testmot5 = motor(PORT15, ratio18_1);
motor testmot6 = motor(PORT16, ratio18_1, true);
motor_group rightside = motor_group(testmot, testmot2, testmot3);
motor_group leftside = motor_group(testmot4, testmot5, testmot6);
controller Cont1;
digital_out transmission = digital_out(Brain.ThreeWirePort.B);
limit limita = limit(Brain.ThreeWirePort.A);

bool automatic = true;
bool actuate = false;
float speedmod = 1;

/*
std::list<motor>  lists = {
  testmot,
  testmot2
};

lists.
*/


//motor spin function using voltage instead of pct or rpm that makes itself "easy" to use
void motorspin( int motorid, float value, string value_type = "pct", string direction = "fwd"){
  //determines motor spin direction using positive and negative votlages
  int dv;
  if(direction == "fwd"){
    dv = 1;
  }
  else if(direction == "rev"){
    dv = -1;
  }

  //this next part gets ctrl+c and ctrl+v for every motor, with new id's 
  //nothing else worked, but this does

  //determine which motor
  if(motorid == 0){
    //figure out type of input value
    //math is based on a straightend curve value
  
    if(value_type == "pct"){
      rightside.spin(directionType::fwd, (((6*(2*value-120))/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "rpm"){
      rightside.spin(directionType::fwd, (((6*(value-120))/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "volt")
    rightside.spin(directionType::fwd, value*dv, voltageUnits::volt);
  }

  //determine which motor
  if(motorid == 1){
    //figure out type of input value
    //math is based on a straightend curve value
  
    if(value_type == "pct"){
      leftside.spin(directionType::fwd, (((6*(2*value-120))/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "rpm"){
      leftside.spin(directionType::fwd, (((6*(value-120))/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "volt")
      leftside.spin(directionType::fwd, value*dv, voltageUnits::volt);
  }
}

void autoshifter(){
  float watt;
  while(1){
    watt = (rightside.power()+leftside.power())/2;
    if(watt < 0.5){
      speedmod = 1;
      actuate = false;
    }
    else if(watt<1.5){
      speedmod = 0.5;
      actuate = false;
    }
    else if(watt<4){
      speedmod = 1;
      actuate = true;
    }
    else if(watt<4){
      speedmod = 0.5;
      actuate = true;
    }
    wait(0.0000000000000000001,msec);
  }
}

void manualshifter(){
  int cycle = 0;
  while(1){
    if(Cont1.ButtonX.pressing() & (cycle == 0)){
      speedmod = 1;
      actuate = false;
      cycle = 1;
    }
    else if(Cont1.ButtonX.pressing() & (cycle == 1)){
      speedmod = 0.5;
      actuate = false;
      cycle = 2;
    }
    else if(Cont1.ButtonX.pressing() & (cycle == 2)){
      speedmod = 1;
      actuate = true;
      cycle = 3;
    }
    else if(Cont1.ButtonX.pressing() & (cycle == 0)){
      speedmod = 0.5;
      actuate = true;
      cycle = 0;
    }
    wait(1000,msec);
  }
}


//thread parent, controls automatic and manual
void weaver(){
  //sense forchanges and record them
  int mode = 0;
  int cntmode = 0;
  vex::thread autoshift(autoshifter);
  autoshift.detach();
  vex::thread manual(manualshifter);
    manual.detach();
    manual.interrupt();
  while(1){
  if(Cont1.ButtonB.pressing() & (mode == 0)){
    mode = 1;
    automatic = false;
  }
  else if(Cont1.ButtonB.pressing() & (mode == 1)){
    mode = 0;
    automatic = true;
  }

  if((!automatic) & (cntmode == 1)){
    vex::thread manual(manualshifter);
    manual.detach();
    autoshift.interruptAll();
    cntmode = 0;
  }
  else if (automatic & (cntmode == 0)){
  vex::thread autoshift(autoshifter);
  autoshift.detach();
  manual.interruptAll();
  cntmode = 1;
  }
  wait(3, sec);
  }
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  vex::thread shifting(weaver);
  shifting.detach();
  while(1){
   transmission.set(actuate);
   motorspin(0, 100*speedmod);
   motorspin(1, 100*speedmod);
   wait(2, timeUnits::msec);
  }
}

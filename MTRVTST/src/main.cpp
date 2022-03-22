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
motor testmot2 = motor(PORT12, ratio18_1);
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
      testmot.spin(directionType::fwd, (((6*(2*value)-120)/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "rpm"){
      testmot.spin(directionType::fwd, (((6*(value)-120)/125)+6)*dv, voltageUnits::volt);
    }
    else if(value_type == "volt")
    testmot.spin(directionType::fwd, value*dv, voltageUnits::volt);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while(1){
    motorspin(0, 100);
    wait(1, sec);
    motorspin(0, 50, "rpm", "rev");
    wait(1, sec);
  }
}

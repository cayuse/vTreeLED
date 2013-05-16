#include "Arduino.h"
#include "vTreeLEDControl.h"

/**
	
*/
vTreeLEDControl::vTreeLEDControl() {
    vTreeLEDCall = false;
    northCall = false;
    southCall = false;

    ditchCurr = 0;
    ditchSum = 0;
    ditchCount = 0;

    sumpCurr = 0;
    sumpSum = 0;
    sumpCount = 0;

    sumpLowTrigger = 0;
    enableSumpTrigger = false;
    
    // Configure Pins
  
  // vTreeLED and Valve controls
  // High is off, low is on.
  digitalWrite(vTreeLEDControl::vTreeLEDPin,HIGH);
  pinMode(vTreeLEDControl::vTreeLEDPin,OUTPUT);
  
  digitalWrite(vTreeLEDControl::southPin,HIGH);
  pinMode(vTreeLEDControl::southPin,OUTPUT);
  
  digitalWrite(vTreeLEDControl::northPin,HIGH);
  pinMode(vTreeLEDControl::northPin,OUTPUT);
    
}

vTreeLEDControl::~vTreeLEDControl() {}

void vTreeLEDControl::setSumpTrigger(int lvl) {
    sumpLowTrigger = lvl;
}

void vTreeLEDControl::setSumpTriggerEnable(bool bOn) {
    enableSumpTrigger = bOn;
}

bool vTreeLEDControl::isvTreeLEDOn() {
  int pin = digitalRead(vTreeLEDControl::vTreeLEDPin);
  if (pin == LOW) {
    return true;
  }
  return false;
}

bool vTreeLEDControl::isNorthOn() {
  int pin = digitalRead(vTreeLEDControl::northPin);
  if (pin == LOW) {
    return true;
  }
  return false;
}

bool vTreeLEDControl::isSouthOn() {
  int pin = digitalRead(vTreeLEDControl::southPin);
  if (pin == LOW) {
    return true;
  }
  return false;
}

void vTreeLEDControl::setvTreeLED(bool bOn) {
  if (bOn) {
    vTreeLEDCall = true;
    digitalWrite(vTreeLEDControl::vTreeLEDPin,LOW);
  } else {
    vTreeLEDCall = false;
    digitalWrite(vTreeLEDControl::vTreeLEDPin,HIGH);
  }
}

void vTreeLEDControl::setNorthCall(bool bOn) {
  northCall = bOn;
}

void vTreeLEDControl::setNorthValve(bool bOn) {
  if (bOn) {
    digitalWrite(vTreeLEDControl::northPin,LOW);
  } else {
    digitalWrite(vTreeLEDControl::northPin,HIGH);
  }
}

void vTreeLEDControl::setSouthCall(bool bOn) {
  southCall = bOn;
}

void vTreeLEDControl::setSouthValve(bool bOn) {
  if (bOn) {
    digitalWrite(vTreeLEDControl::southPin,LOW);
  } else {
    digitalWrite(vTreeLEDControl::southPin,HIGH);
  }
}

void vTreeLEDControl::Loop() {
    levelChecks();
    updateValves();
}

void vTreeLEDControl::levelChecks() {
    if (enableSumpTrigger && sumpCurr < sumpLowTrigger) {
      setvTreeLED(false);
    } else {
      setvTreeLED(vTreeLEDCall);
    }
}

/*
  Called once a second.
  If the vTreeLED is off, then force both valves off.
*/
void vTreeLEDControl::updateValves() {
  if (isvTreeLEDOn() ) {
    setNorthValve(northCall);
    setSouthValve(southCall);
  } else {
    // Always turn valves off if the vTreeLED
    // is off.
    setNorthValve(false);
    setSouthValve(false);
  }
}

/*
  Called often.. reads sensors and applies hardware
  averaging.
*/
void vTreeLEDControl::readSensors() {
  int ditch = analogRead(vTreeLEDControl::ditchPin);
  int sump = analogRead(vTreeLEDControl::sumpPin);

  ditchSum += ditch;
  ditchCount++;
  if (ditchCount >= 1000) {
    double ditchD = ditchSum;
    ditchD /= (double)ditchCount;
    ditchCurr = (int)ditchD;
    ditchCount = 0;
    ditchSum = 0;
  }

  sumpSum += sump;
  sumpCount++;
  if (sumpCount >= 1000) {
    double sumpD = sumpSum;
    sumpD /= (double)sumpCount;
    sumpCurr = (int)sumpD;
    sumpCount = 0;
    sumpSum = 0;
  }
}


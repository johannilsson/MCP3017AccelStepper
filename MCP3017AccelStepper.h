// MCP3017AccelStepper.h
//
// MCP23017 I2C AccelStepper library for Arduino
//
// Extends the Arduino AccelStepper library to add support for the MCP23017 I2C I/O expander.
//
// License GPL V2, same as AccelStepper (http://www.airspayce.com/mikem/arduino/AccelStepper/)
//
// Author Johan Nilsson (http://www.markupartist.com)
// Copyright (C) 2013 Johan Nilsson

#ifndef MCP3017AccelStepper_h
#define MCP3017AccelStepper_h

#include <stdlib.h>
#include <Arduino.h>
#include <Wire.h>
#include <AccelStepper.h>
#include <Adafruit_MCP23017.h>

class MCP3017AccelStepper : public AccelStepper {
  public:
  MCP3017AccelStepper();
  MCP3017AccelStepper(uint8_t interface = AccelStepper::FULL4WIRE, uint8_t pin1 = 2, uint8_t pin2 = 3, uint8_t pin3 = 4, uint8_t pin4 = 5);
  void setMcp(Adafruit_MCP23017 mcp);
  void setOutputPins(uint8_t mask);
  void disableOutputs();
  void enableOutputs();
  void setEnablePin(uint8_t enablePin);
  
private:
  AccelStepper _accelStepper;
  Adafruit_MCP23017 _mcp;
  bool _usingMcp;
  void _digitalWrite(uint8_t pin, uint8_t value);
  void _pinMode(uint8_t pin, uint8_t value);
};

#endif

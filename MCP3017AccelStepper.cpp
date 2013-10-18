// MCP3017AccelStepper.cpp
//
// Copyright (C) 2013 Johan Nilsson

#include "MCP3017AccelStepper.h"

MCP3017AccelStepper::MCP3017AccelStepper() {

}


MCP3017AccelStepper::MCP3017AccelStepper(uint8_t interface, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) : _accelStepper(interface, pin1, pin2, pin3, pin4) {
  _interface = interface;
  _currentPos = 0;
  _targetPos = 0;
  _speed = 0.0;
  _maxSpeed = 1.0;
  _acceleration = 1.0;
  _sqrt_twoa = 1.0;
  _stepInterval = 0;
  _minPulseWidth = 1;
  _enablePin = 0xff;
  _lastStepTime = 0;
  _pin[0] = pin1;
  _pin[1] = pin2;
  _pin[2] = pin3;
  _pin[3] = pin4;

  if (_interface == DRIVER) {
    _enablePin = pin3;
  }

  _usingMcp = false;
  _n = 0;
  _c0 = 0.0;
  _cn = 0.0;
  _cmin = 1.0;
  _direction = DIRECTION_CCW;

  int i;
  for (i = 0; i < 4; i++) {
    _pinInverted[i] = 0;
  }
}

void MCP3017AccelStepper::setMcp(Adafruit_MCP23017 mcp) {
  _usingMcp = true;
  _mcp = mcp;
}

void MCP3017AccelStepper::setOutputPins(uint8_t mask) {
  uint8_t numpins = 2;
  if (_interface == FULL4WIRE || _interface == HALF4WIRE) {
    numpins = 4;
  }

  uint8_t i;
  for (i = 0; i < numpins; i++) {
    _digitalWrite(_pin[i], (mask & (1 << i)) ? (HIGH ^ _pinInverted[i]) : (LOW ^ _pinInverted[i]));
  }
}

void MCP3017AccelStepper::disableOutputs() {
  if (! _interface) {
    return;
  }
  
  setOutputPins(0); // Handles inversion automatically
  if (_enablePin != 0xff) {
    _digitalWrite(_enablePin, LOW ^ _enableInverted);
  }
}

void MCP3017AccelStepper::enableOutputs() {
  if (! _interface) {
    return;
  }

  _pinMode(_pin[0], OUTPUT);
  _pinMode(_pin[1], OUTPUT);

  if (_interface == FULL4WIRE || _interface == HALF4WIRE) {
    _pinMode(_pin[2], OUTPUT);
    _pinMode(_pin[3], OUTPUT);
  }

  if (_enablePin != 0xff) {
    _pinMode(_enablePin, OUTPUT);
    _digitalWrite(_enablePin, HIGH ^ _enableInverted);
  }
}

void MCP3017AccelStepper::setEnablePin(uint8_t enablePin) {
  _enablePin = enablePin;

  // This happens after construction, so init pin now.
  if (_enablePin != 0xff) {
    _pinMode(_enablePin, OUTPUT);
    _digitalWrite(_enablePin, HIGH ^ _enableInverted);
  }
}

void MCP3017AccelStepper::_digitalWrite(uint8_t pin, uint8_t value) {
  if (_usingMcp == true) {
    _mcp.digitalWrite(pin, value);
  } else {
    digitalWrite(pin, value);
  }
}

void MCP3017AccelStepper::_pinMode(uint8_t pin, uint8_t value) {
  if (_usingMcp == true) {
    _mcp.pinMode(pin, value);
  } else {
    pinMode(pin, value);
  }
}


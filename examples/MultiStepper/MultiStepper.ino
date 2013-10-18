#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <AccelStepper.h>
#include <MCP3017AccelStepper.h>

Adafruit_MCP23017 mcp1;
MCP3017AccelStepper stepper1(AccelStepper::DRIVER, 2, 1); // interface, step, dir
MCP3017AccelStepper stepper2(AccelStepper::DRIVER, 13, 14); // interface, step, dir
MCP3017AccelStepper stepper3(AccelStepper::DRIVER, 5, 4); // interface, step, dir

void setup() {
  Serial.begin(9600);

  mcp1.begin();

  setMicrostep(mcp1);

  // Stepper 1
  stepper1.setMcp(mcp1);
  stepper1.setMinPulseWidth(800);
  stepper1.setPinsInverted(false, false, true);
  stepper1.setEnablePin(0);
  stepper1.enableOutputs();
  stepper1.setMaxSpeed(300.0);
  stepper1.setAcceleration(100.0);

  // Stepper 2
  stepper2.setMcp(mcp1);
  stepper2.setMinPulseWidth(800);
  stepper2.setPinsInverted(false, false, true);
  stepper2.setEnablePin(15);
  stepper2.enableOutputs();
  stepper2.setMaxSpeed(300.0);
  stepper2.setAcceleration(100.0);

  // Stepper 3
  stepper3.setMcp(mcp1);
  stepper3.setMinPulseWidth(800);
  stepper3.setPinsInverted(false, false, true);
  stepper3.setEnablePin(3);
  stepper3.enableOutputs();
  stepper3.setMaxSpeed(300.0);
  stepper3.setAcceleration(100.0);

  stepper1.moveTo(600);
  stepper2.moveTo(600);
  stepper3.moveTo(600);
}

void loop() {
  if (stepper1.distanceToGo() == 0) {
    stepper1.moveTo(-stepper1.currentPosition());
  }

  stepper1.run();
  stepper2.run();
  stepper3.run();
}

void setMicrostep(Adafruit_MCP23017 mcp) {

  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(8, OUTPUT);

  mcp.digitalWrite(10, LOW);
  mcp.digitalWrite(9, LOW);
  mcp.digitalWrite(8, LOW);
}


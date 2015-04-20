
# MCP23017 I2C AccelStepper library for Arduino

Extension for the [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/) library.

With this library AccelStepper can be used to control steppers using a MCP23017 I/O Expander over I2C interface. This requires only two pins to be used `A4` SDA and `A5` SCL on the Arduino Uno. MCP23017AccelStepper extends AccelStepper which means that all the functionality of AccelStepper is still there.

* I2C support using a MCP23017 I/O Expander.
* When used with the driver interface the third pin for the constructor can be used to set the enable pin.
* By not calling `setMcp` it will fallback to the Arduino pins.

## Example

    #include <Wire.h>
    #include <Adafruit_MCP23017.h>
    #include <AccelStepper.h>
    #include <MCP3017AccelStepper.h>

    #define STEPPER_COUNT 4

    Adafruit_MCP23017 mcp1;

	MCP3017AccelStepper steppers[STEPPER_COUNT] = {
	    // interface, step, dir, en
  	    MCP3017AccelStepper(AccelStepper::DRIVER, 15, 14, 8),
  	    MCP3017AccelStepper(AccelStepper::DRIVER, 4, 5, 6),
  	    MCP3017AccelStepper(AccelStepper::DRIVER, 12, 11, 10),
  	    MCP3017AccelStepper(AccelStepper::DRIVER, 3, 1, 2),
	};

    void setup() {
      mcp1.begin();
  
      for (int i = 0; i < STEPPER_COUNT; i++) {
        steppers[i].setMcp(mcp1);
        steppers[i].enableOutputs();
        steppers[i].setMaxSpeed(150.0);
        steppers[i].setAcceleration(100.0);
        steppers[i].moveTo(200);
      }
    }

    void loop() {
  	  if (steppers[0].distanceToGo() == 0) {
        steppers[0].moveTo(-steppers[0].currentPosition());
      }

      for (int i = 0; i < STEPPER_COUNT; i++) {
        steppers[i].run();
      }
    }

## Making things run smooth

Ones you have a couple of steppers running you might notice that they're a bit slow. To make them run smooth you can change the clock frequency of the I2C bus. More on this here <http://playground.arduino.cc/Code/ATMELTWI#line7>

    mcp1.begin();
    TWBR = 12;  // 400 kHz 
    // TWBR = 72;  // 100 kHz (default)

## Dependencies

External dependencies, the Wire library is also needed but is bundled with the Arduino software.

* [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper/)
	* Private methods of the AccelStepper library must be modified to be protected.
* [Adafruit MCP23017](https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library)

### License

GPL V2, same as AccelStepper <http://www.airspayce.com/mikem/arduino/AccelStepper/>

### Author

2013 Johan Nilsson <http://www.markupartist.com>








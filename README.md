 ArduinoBasicIO
=================
 
Object oriented library containing classes intended to make Arduino pins and components handling easier. These classes may be useful when used as base classes to extend.
It may also be useful for learning/teaching an object oriented approach to Arduino.
TODO Documented <a href="https://github.com/stompp/ArduinoBasicIO">here.</a>


  Objects
-----------------------------------
Classes for real objects
* SimpleLed
  
  Led class.
  
* SimplePotentiometer
  
  Potentiometer class.

* DinamicPulseTrainDetector

  Detects pulses dinamically. This are not full pulses it just detects the exact desired number of pulses at pulse level with a period between DEFAULT_MIN_DELAY and DEFAULT_MAX_DELAY.
  TODO improve
  
* KnockSwitch
  
  Pulse train based switch. 
	
Basic pin operations
---------------------
Defind in ArduinoIOPins.h
* ArduinoPin 

  Base class for Arduino pins. It contains all basic pin functions such for pin setting, input reading and output writing.
 
* AnalogInputPin

  Analog pin extension. By now, just average reading extension included.
  
* DigitalInputPin

  Digital input pin abstraction. Includes methods for input reading and change detection. Input state is whatched.
  
  - Use isHigh() or isLow() to check input.
  - inputChanged(), raisingChaned() and fallingChanged() will check for input changes.
 
* DigitalOutputPin

  Digital output pin abstraction. This pin class whatches for output state when tracking is needed.
  
  - Value writing will be stored.
  - high() and low() methods write HIGH or LOW to output.
  - changeState() Inverts the output state.

  "Switched" input pins
-------------------------
Defined in BaseInputs.h

* SwitchedInputBase 
  
  Base class for making on/off switched input.
  
* SwitchedInput
  
  An easier way of handling digital inputs.	Choose the value to consider this input on at input init.
 
* LowOnSwitchedInput
  
  An easier way of handling digital inputs considered ON when input is LOW .
  Use this instead of SwitchedInput if you want it lighter.
 
* HighOnSwitchedInput
  
  An easier way of handling digital inputs considered ON when input is HIGH.
  Use this instead of SwitchedInput if you want it lighter.

 
  "Actuator-like" output pins
-----------------------------------
Defined in BaseOutputs.h
* ActuatorBase
  
  Base class for making on/off actuators such as relays,leds,and so on.
  
* DigitalActuator
  
  An easier way of handling on/off actuators. Choose the type of on/off actuator you're using by indicating the digital value that will turn it on.
 
* LowOnActuator class
  
  An easier way of handling on/off actuators which are turned on by writing a LOW level.
  Use this instead of DigitalActuator if you want it lighter.
 
* HighOnActuator class
  
  An easier way of handling on/off actuators which are turned on by writing a HIGH level. Use this instead of DigitalActuator if you want it lighter.
 





 

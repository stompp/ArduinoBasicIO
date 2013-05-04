#ifndef BASEOUTPUTS_H_
#define BASEOUTPUTS_H_

#include "ArduinoIOPins.h"

/*
 * Base class for making on/off actuators such as relays,leds,and so on.
 */
class ActuatorBase : public DigitalOutputPin {

public :
	/** Default constructor */
	ActuatorBase () : DigitalOutputPin(){}
	/** Pin setting included constructor. */
	ActuatorBase(uint8_t pin): DigitalOutputPin(pin){off();}
	virtual ~ActuatorBase(){}
	/** Turn it on */
	virtual void on()   =0;
	/** Turn it off */
	virtual void off()  =0;
	/** Check if it's on */
	virtual bool isOn() {return outputState > 0;}
	/** Check if it's off */
	virtual bool isOff(){return !isOn();}
protected :
	/** Output pin initialization to off. State is off*/
	virtual void initActuator(uint8_t pin){
		initOutput(pin);
		off();
	}
};

/**
 * An easier way of handling on/off actuators.
 * Choose the type of basic actuator you're using by indicating
 * the value that turns the actuator on.
 */
class DigitalActuator : protected ActuatorBase {

protected :
	uint8_t highOn;
public :
	/** Default constructor */
	DigitalActuator () : ActuatorBase(){}
	/** Pin setting included constructor. */
	DigitalActuator(uint8_t pin, uint8_t onLevel = true): ActuatorBase(pin),highOn(onLevel){off();}
	virtual ~DigitalActuator(){}

	/** Output pin initialization to off.
	 * @param onLevel Digital level for turning the actuator on,opened,whatever.
	 * HIGH,true or any number bigger than 0 means the opposite of LOW,false or 0.
	 */
	void initActuator(uint8_t pin, uint8_t onLevel = true){
		highOn = onLevel;
		ActuatorBase::initActuator(pin);

	}

	/** Turn it on */
	virtual void on()  {writeDigital(highOn);}
	/** Turn it off */
	virtual void off()  {writeDigital(!highOn);};
	/** Check if it's on */
	virtual bool isOn() {return (highOn) ? isHigh() : isLow();}
	/** Check if it's off */
	virtual bool isOff(){return !isOn();}
};

/**
 * An easier way of handling on/off actuators which are turned ON
 * by writing a LOW level. Use this instead of DigitalActuator if you
 * want it lighter.
 */
class LowOnActuator : public ActuatorBase {
public :
	/** Default constructor */
	LowOnActuator () : ActuatorBase(){}
	/** Pin setting included constructor. */
	LowOnActuator(uint8_t pin): ActuatorBase(pin){off();}
	virtual ~LowOnActuator(){}
	/** Turn it on */
	void on(){ low();}
	/** Turn it off */
	void off(){ high();}
	/** Check if it's on */
	bool isOn() {return isLow();}
	/** Check if it's off */
	bool isOff() {return isHigh();}


};

/**
 *
 * An easier way of handling on/off actuators which are turnedON
 * by writing a HIGH level. Use this instead of DigitalActuator if you
 * want it lighter.
 */
class HighOnActuator : public ActuatorBase {
public :
	/** Default constructor */
	HighOnActuator () : ActuatorBase(){}
	/** Pin setting included constructor. */
	HighOnActuator(uint8_t pin): ActuatorBase(pin){off();}

	virtual ~HighOnActuator(){}
	/** Turn it on */
	virtual void on(){ high();}
	/** Turn it off */
	virtual void off(){ low();}
	/** Check if it's on */
	virtual bool isOn() {return isHigh();}
	/** Check if it's off */
	virtual bool isOff() {return isLow();}


};



#endif /* BASEOUTPUTS_H_ */

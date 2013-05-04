#ifndef BASEINPUTS_H_
#define BASEINPUTS_H_

#include "ArduinoIOPins.h"
/**
 * Base class for making on/off switched input
 */
class SwitchedInputBase : public DigitalInputPin{

public :
	SwitchedInputBase () : DigitalInputPin(){}
	SwitchedInputBase(uint8_t pin) : DigitalInputPin(pin){}
	virtual ~SwitchedInputBase(){}
	/** Check if it's on */
	virtual bool isOn() = 0;
	/** Check if it's off */
	virtual bool isOff() = 0;
};

/**
 * An easier way of handling digital inputs.
 * Choose the value to consider this input on at @initInput.
 */
class SwitchedInput : public SwitchedInputBase{

private :
	bool highOn;
public :
	/** Default constructor */
	SwitchedInput () : SwitchedInputBase(){}
	/** Pin setting included constructor. */
	SwitchedInput(uint8_t pin, uint8_t onLevel = true) : SwitchedInputBase(pin){highOn = onLevel;}

	virtual ~SwitchedInput(){}

	/** Input pin initialization.
	 * @param pin Input pin
	 * @param onLevel Digital level for considering the input on,opened,whatever.
	 * HIGH,true or any number bigger than 0 mean the opposite to LOW,false or 0.
	 */
	void initInput(uint8_t pin, uint8_t onLevel = true){
		highOn = onLevel;
		DigitalInputPin::initInput(pin);
	}
	/** Check if it's on */
	virtual bool isOn(){ return ((highOn) ? isHigh():isLow());}
	/** Check if it's off */
	virtual bool isOff(){ return !this->isOn();}
};

/**
 * An easier way of handling digital inputs considered ON when input is LOW .
 * Use this instead of SwitchedInput if you want it lighter.
 */

class LowOnSwitchedInput : public SwitchedInputBase {

public :
	/** Default constructor */
	LowOnSwitchedInput () : SwitchedInputBase(){}
	/** Pin setting included constructor. */
	LowOnSwitchedInput(uint8_t pin) : SwitchedInputBase(pin){}
	virtual ~LowOnSwitchedInput(){}
	/** Check if it's on */
	virtual bool isOn() {return isLow();}
	/** Check if it's off */
	virtual bool isOff() {return isHigh();}
};
/**
 * HighOnSwitchedInput class
 * An easier way of handling digital inputs considered ON when input is HIGH.
 * Use this instead of SwitchedInput if you want it lighter.
 */
class HighOnSwitchedInput : public SwitchedInputBase {

public :
	/** Default constructor */
	HighOnSwitchedInput () : SwitchedInputBase(){}
	/** Pin setting included constructor. */
	HighOnSwitchedInput(uint8_t pin) : SwitchedInputBase(pin){}
	virtual ~HighOnSwitchedInput(){}
	/** Check if it's on */
	virtual bool isOn() {return  isHigh();}
	/** Check if it's off */
	virtual bool isOff() {return isLow();}
};



#endif /* BASEINPUTS_H_ */

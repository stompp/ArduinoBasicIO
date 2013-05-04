#ifndef ARDUINOIOPINS_H_
#define ARDUINOIOPINS_H_

#if ARDUINO < 100
#include "WProgram.h"
#else
#include "Arduino.h"
#endif

/** Basic Arduino pin methods class */
class ArduinoPin {
protected :
	/** pin number */
	uint8_t arduinoPin;
public :
	/** Default constructor */
	ArduinoPin(){}
	/** Pin setting included constructor. */
	ArduinoPin(uint8_t pin) : arduinoPin(pin){}
	/** Destructor */
	virtual ~ArduinoPin(){}

	// Pin setting

	/** Pin mode setting */
	void setPinMode(uint8_t mode){pinMode(arduinoPin,mode);}
	/** Pin and mode setting */
	void setPin(uint8_t pin){arduinoPin = pin;}

	// Pin init

	/** Pin and mode setting */
	void initPin(uint8_t pin, uint8_t mode){setPin(pin);setPinMode(mode);}
	/** Pin initialization as Output */
	void initOutput(uint8_t pin) {initPin(pin,OUTPUT);}
	/** Pin initialization as Input */
	void initInput(uint8_t pin) {initPin(pin,INPUT);}
	/** Sets pin mode to OUTPUT */
	void initOutput(){setPinMode(OUTPUT);}
	/** Sets pin mode to INPUT */
	void initInput() {setPinMode(INPUT);}

	// Value Reading

	/** digitalRead */
	virtual int readDigital(){return digitalRead(arduinoPin);}
	/** analogRead */
	virtual int readAnalog(){return analogRead(arduinoPin);}

	// Value Writing

	/** digitalWrite  */
	virtual void writeDigital(uint8_t value){digitalWrite(arduinoPin,value);}
	/** analogWrite (PWM)  */
	virtual void writeAnalog(uint8_t value){analogWrite(arduinoPin,value);}


};

/**
 * Digital input pin abstraction. Includes methods for input reading and change detection. Input state is whatched.
 * - Use isHigh() or isLow() to check input.
 * - inputChanged(), raisingChaned() and fallingChanged() will check for input changes.
 */
class DigitalInputPin : public ArduinoPin{

public :
	uint8_t lastInput;
	/** Default constructor */
	DigitalInputPin () : ArduinoPin(){}
	/** Pin setting included constructor. */
	DigitalInputPin(uint8_t pin) : ArduinoPin(pin){initInput();}
	virtual ~DigitalInputPin(){}

	/** Checks if input is HIGH */
	bool isHigh(){lastInput = readDigital();return lastInput;}
	/** Checks if input is LOW */
	bool isLow(){return !isHigh();}

	// Change detection

	/** Checks if input state changed */
	bool inputChanged(){
		bool i = lastInput;
		return (i!=isHigh());
	}
	/** Checks if input state changed from LOW to HIGH */
	bool raisingChanged(){
		bool i = lastInput;
		return i == false ?  isHigh(): false;
	}
	/** Checks if input state changed from HIGH to LOW */
	bool fallingChanged(){
		bool i = lastInput;
		return i == true ?  isLow(): false;
	}

};

/** Analog pin extension. By now, just average reading extension included.*/
class AnalogInputPin : public ArduinoPin{

public :

	/** Default constructor */
	AnalogInputPin () : ArduinoPin(){}
	/** Pin setting included constructor. */
	AnalogInputPin(uint8_t pin) : ArduinoPin(pin){initInput();}
	/** Destructor */
	virtual ~AnalogInputPin(){}

	/**
	 * Gets an average meausure given the number of samples. Reading is static.
	 * @param nSamples Number of consecutive samples to take for the meausure
	 */
	int readAverage(unsigned int nSamples){
		unsigned long value = 0;
		unsigned int n=0;
		while(n++ < nSamples){value += (readAnalog());}
		return value/nSamples;
	}
	/**
	 * Gets an average meausure given the number of samples and sample period. Reading is static.
	 * @param nSamples Number of consecutive samples to take.
	 * @param period Sample period un miliseconds
	 */
	int readAverage(unsigned int nSamples,unsigned int period){

		unsigned long value = 0;
		unsigned long micros = 1000*period - 215;
		unsigned int n=0;
		while(n++ < nSamples){value += (readAnalog());delayMicroseconds(micros);}
		return value/nSamples;

	}

	uint8_t to8bit(int n){return map(n,0,1024,0,255);}
	uint8_t readto8bit(){return to8bit(readAnalog());}

};


/** Digital output pin abstraction. This pin class whatches for output state when tracking is needed.
 *  - Value writing will be stored.
 *  - high() and low() methods write HIGH or LOW to output.
 *  - changeState() Inverts the output state.
 *
 */
class DigitalOutputPin : public ArduinoPin{

protected :
	uint8_t outputState;
	void storeOutputValue(uint8_t newValue){outputState = newValue;}

public :
	/** Default constructor */
	DigitalOutputPin () : ArduinoPin(){}
	/** Pin setting included constructor. */
	DigitalOutputPin(uint8_t pin) : ArduinoPin(pin){initOutput();}
	virtual ~DigitalOutputPin(){}

	// Output writing.

	/** Writes and stores state to output */
	virtual void writeDigital(uint8_t state){
		storeOutputValue(state);
		ArduinoPin::writeDigital(outputState);
	}
	/** Writes and stores PWM value on output */
	virtual void writeAnalog(uint8_t value){
		storeOutputValue(value);
		ArduinoPin::writeAnalog(outputState);
	}
	/** Sets output to high */
	void high(){writeDigital(HIGH);}
	/** Sets output to low */
	void low(){writeDigital(LOW);}
	/** Inverts the state of the output */
	void changeState(){writeDigital(!outputState);}

	// Output checking.

	/** Checks if output was set to High */
	virtual bool isHigh(){return outputState;}
	/** Checks if output was set to Low */
	virtual bool isLow(){return !outputState;}
	/** Returns last stored value/state */
	uint8_t outputValue(){ return outputState;}


};





#endif /* ARDUINOIOPINS_H_ */

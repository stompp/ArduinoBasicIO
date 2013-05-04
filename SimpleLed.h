/*
 * SimpleLed.h
 *
 *  Created on: 27/01/2013
 *      Author: Juan
 */

#ifndef SIMPLELED_H_
#define SIMPLELED_H_

#include "BaseOutputs.h"

#define SLED_OFF 0x00
#define SLED_ON 0xff
#define STATE_NORMAL 0
#define STATE_BLINKING 1
#define INFINITE_LOOP 2

typedef struct {
	uint8_t times;
	uint8_t counter;
	uint16_t delay;
	unsigned long lastChange;
	uint8_t state;
} BlinkAtt;

class SimpleLed : public ActuatorBase {

private:
	BlinkAtt *blinkAtt;
	//uint8_t pin;
	boolean pinIsPWM;
	uint8_t ledState;
	uint8_t level;
public:
	SimpleLed();
	virtual ~SimpleLed();

	void initLed(uint8_t ledPin, boolean isPWM = true);
	void setLevel(uint8_t newLevel);
	virtual void emit(uint8_t level);
	void on();
	void off();
	virtual void reset();
	void staticBlink(uint16_t times, uint16_t period);
	void dinamicTimedBlink(uint16_t howLong, uint16_t period);
	void dinamicRepeatedBlink(uint16_t times, uint16_t period);
	void dinamicBlink(uint16_t period);

	void update();
};

#endif /* SIMPLELED_H_ */

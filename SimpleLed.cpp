#include "SimpleLed.h"


SimpleLed::SimpleLed() : ledState(STATE_NORMAL),level(SLED_ON){}
SimpleLed::~SimpleLed() {}

/**
 * Inits led
 * @param ledPin Arduino pin number
 * @param isPWM Say true if pin is PWM
 */
void SimpleLed::initLed(uint8_t ledPin, boolean isPWM){
	pinIsPWM = isPWM;
	initActuator(ledPin);
	off();

}
/** Sets led output level
 * @param newLevel Pin set as PWM (0-255), Digital (0,1)*/
void SimpleLed::setLevel(uint8_t newLevel){level = newLevel;}
/** Makes led emit level*/
void SimpleLed::emit(uint8_t level){(pinIsPWM) ? writeAnalog(level) : writeDigital((bool)level) /*? digitalWrite(pin,HIGH) : digitalWrite(pin,LOW)*/;}
/** Turns on writting set level  */
void SimpleLed::on(){emit(level);}
/** Turns off writting 0 */
void SimpleLed::off(){emit(SLED_OFF);}
/** Makes led blink blocking
 * @param times Number of times to blink
 * @param periodo Blinking periodin milliseconds, duty cicle is 50%
 */
void SimpleLed::staticBlink(uint16_t times, uint16_t period){

	uint16_t d = period/2;
	uint16_t n = 0;
	while(n++ < times){
		on();
		delay(d);
		off();
		delay(d);
	}
}

/** Makes led blink dinamically without blocking. Use update()
 * to update led state.
 * @param times Number of times to blink
 * @param periodo Blinking period in milliseconds, duty cicle is 50%
 */
void SimpleLed::dinamicRepeatedBlink(uint16_t times, uint16_t period){
	if(ledState == STATE_NORMAL){
//		free(&blinkAtt);
		blinkAtt = new BlinkAtt;
	}
		blinkAtt->times = times;
		blinkAtt->counter = 0;
		blinkAtt->delay = period/2;
		blinkAtt->state = SLED_ON;
		on();
		blinkAtt->lastChange = millis();
		ledState = STATE_BLINKING;
}

/** Makes led blink dinamically.Use update() to update led state.
 * @param period Blinking period in milliseconds, duty cicle is 50%
 */
void SimpleLed::dinamicBlink(uint16_t period){
	dinamicRepeatedBlink(0,period);
	ledState = INFINITE_LOOP;
}
/** Makes led blink dinamically.Use update() to update led state.
 * @howLong Time kept blinking.
 * @param period Blinking period in milliseconds, duty cicle is 50%
 */
void SimpleLed::dinamicTimedBlink(uint16_t howLong, uint16_t period){
	dinamicRepeatedBlink(round(howLong/period),period);
}
/**
 * Updates led state. To be used when dinamically blinking.
 */
void SimpleLed::update(){

	if(ledState != STATE_NORMAL){
		if((millis() - blinkAtt->lastChange) >= blinkAtt->delay) {

			if(blinkAtt->state == SLED_ON){
				off();
				blinkAtt->lastChange = millis();
				blinkAtt->state = SLED_OFF;
				if((ledState != INFINITE_LOOP) && (++blinkAtt->counter >= (blinkAtt->times-1))){reset();}

			}else{
				on();
				blinkAtt->lastChange = millis();
				blinkAtt->state = SLED_ON;
			}


		}
	}
}

/**
 * Resets blinking and turns led off.
 */
void SimpleLed::reset(){

	if(ledState != STATE_NORMAL){
		off();
		delete blinkAtt;
		ledState = STATE_NORMAL;
	}

}


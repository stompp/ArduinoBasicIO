/*
 * PulseTrainDetector.h
 *
 *  Created on: 08/03/2013
 *      Author: Juan
 */

#ifndef PULSETRAINDETECTOR_H_
#define PULSETRAINDETECTOR_H_

#include "BaseInputs.h"
#define DEFAULT_MIN_DELAY 100
#define DEFAULT_MAX_DELAY 400

/**
 * Detects pulses dinamically. This are not full pulses it just detects
 * the exact desired number of pulses at pulse level with a period between DEFAULT_MIN_DELAY and DEFAULT_MAX_DELAY.
 * TODO improve
 */
class DinamicPulseTrainDetector : private SwitchedInput{

public :
	DinamicPulseTrainDetector(){}
	virtual ~DinamicPulseTrainDetector(){}

private :

   // time whatching
   unsigned long lastEvent;
   // pulse train variables
   uint8_t expectedPulses;
   uint8_t leftPulses;
   // "pulse width" & "max pulse period"
   unsigned int minPulsedelay;
   unsigned int maxPulseDelay;


public :

   /** Sets the number of pulses to search */
   void setExpectedPulses(uint8_t pulses){
	   //if(pulses < 2 ) pulses = 2;
	   expectedPulses = leftPulses = pulses;
   }
   /** Sets delays between pulses. Pulses must occur between these values.
    * @param minDelay Minimum delay between pulses
    * @param minDelay Maximum delay between pulses.
    */
   void setDelays(unsigned int minDelay,unsigned int maxDelay){
	   maxPulseDelay = maxDelay;
	   minPulsedelay = minDelay;
   }
   /** Inits detector
    * @param pulsePin Digital pin number for pulses input
    * @param pulseOnLevel Digital level to consider ON [0,1]
    */
   void initDetector(uint8_t pulsePin, uint8_t pulseOnLevel){
	   initInput(pulsePin,pulseOnLevel);
	   lastEvent = millis();
	   setExpectedPulses(2);
	   setDelays(DEFAULT_MIN_DELAY,DEFAULT_MAX_DELAY);
   }

   /** Checks if a pulse train is detected */
   boolean pulseTrainDetected(){

		unsigned long t = millis() - lastEvent;

		// Si no toca leer, salir.
		if(t <= minPulsedelay){return false;}
		
		// toca leer
		// Si pulso off
		if(isOff()){
			if(leftPulses==0){
				leftPulses = expectedPulses;
				boolean fin = true;
				while((fin = isOff())  && ((t = millis() - lastEvent) < maxPulseDelay));
				lastEvent += t;
				return fin;
			}
			if(t > maxPulseDelay) leftPulses = expectedPulses;
			return false; 
		}

		// pulso ON

		// Inicio

		if(leftPulses == expectedPulses){
			if(t > maxPulseDelay){leftPulses--;}
			lastEvent += t;
			return false;
		}
		
		// dentro del tiempo esperado -> restamos pulso esperado
		if(t <= maxPulseDelay){leftPulses--;
		// fuera del tiempo esperado -> lo tomamos como un nuevo pulso inicial
		}else{leftPulses = expectedPulses-1;}
		// registramos evento
		lastEvent += t;
		return false;
		//return resultado;
   }



};


#endif /* PULSETRAINDETECTOR_H_ */

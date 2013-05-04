#ifndef KNOCKSWITCH_H_
#define KNOCKSWITCH_H_


#include "BaseOutputs.h"
#include "PulseTrainDetector.h"

/**
 * Pulse train based switch.
 */
class KnockSwitch : private DinamicPulseTrainDetector, private DigitalActuator{
  
  private :

	uint8_t onK;
	uint8_t offK;

	/** inner state changed setting */
    void setKnocks(){
    	if(DigitalActuator::isOn()) setExpectedPulses(offK);
		else setExpectedPulses(onK);
    }

  public :

    /** Inits switch. Say pins and ON levels. */
    void init(uint8_t switchPin, bool switchOnLevel,uint8_t relayPin, bool relayOnLevel){
    	initDetector(switchPin,switchOnLevel);
    	DigitalActuator::initActuator(relayPin,relayOnLevel);
    }
    
    /** Upadates state. */
    bool update(){
      bool s = pulseTrainDetected();
		if(s){
			DigitalActuator::changeState();
			setKnocks();
		}
    	return s;
    }
    
    /** Sets the number of pulses to turn on the switch */
    void setOnKnocks(uint8_t knocks){onK = knocks;}
    /** Sets the number of pulses to turn off the switch */
    void setOffKnocks(uint8_t knocks){offK = knocks;}
    /** Sets the the same number of knock to turn on/off. */
    void setKnocks(uint8_t knocks){setOnKnocks(knocks);setOffKnocks(knocks);setKnocks();}
    /** Sets the the number of knock to turn on/off. */
    void setKnocks(uint8_t onKnocks,uint8_t offKnocks){setOnKnocks(onKnocks);setOffKnocks(offKnocks);setKnocks();}
	
    /** Check if it's on */
	bool isOn(){return DigitalActuator::isOn();};

    
};
#endif

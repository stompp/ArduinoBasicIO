#include <SimpleLed.h>
#include <SimplePotentiometer.h>


#define POT (A0)
#define LED 3
#define SECTORS 255
SimpleLed led;
SimplePotentiometer pot;

void sectorChangedAction(uint16_t newSector){
	led.emit(newSector);
}
void setup(){
	// inits led as PWM
	led.initLed(LED);
	// inits potentiometer
	pot.initPot(POT,SECTORS);
	// sets action to perform when secor changed
	pot.setOnSectorChangedAction(sectorChangedAction);

}

void loop(){

	pot.update();

}

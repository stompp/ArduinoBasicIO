#include "SimplePotentiometer.h"


SimplePotentiometer::SimplePotentiometer(){

}
/**
 * Inits potentiometer.
 * @param potPin Arduino pin.
 * @param sectors Number of sectors in which analog input will be divided linearly.
 */
void SimplePotentiometer::initPot(uint8_t potPin, uint16_t sectors)  {

	initInput(potPin);
	setSectors(sectors);
	sectorChangedAction = 0;

}
SimplePotentiometer::~SimplePotentiometer() {
	// TODO Auto-generated destructor stub
}

/** Check if sector changed */
boolean SimplePotentiometer::sectorChanged(){

	uint16_t s = getSector();
	if(s!= _lastSector){
		_lastSector = s;
		return true;
	}

	return false;
}
/** Sets action to perform when sector changed. */
void SimplePotentiometer::setOnSectorChangedAction(void(*action)(uint16_t)){ sectorChangedAction = action;}
/** Gets last known sector*/
uint16_t SimplePotentiometer::lastSector(){return _lastSector;}

/** Updates pot activity. If sector changed and setctorChangedAction then will be called-*/
void SimplePotentiometer::update(){

	if(sectorChanged() && (sectorChangedAction != 0)){
		sectorChangedAction(_lastSector);
	}
}

/** Reads value from pot input. */
uint16_t SimplePotentiometer::getValue(){return readAnalog();}

/** Reads sector from pot input. */
uint16_t SimplePotentiometer::getSector(){return readAnalog()/(MAX_SECTORS/sectors);}

/** Sets the number of sectors in which analog input will be divided linearly. Minimum is 1.
 * Sector will be named [0,newSector-1]*/
void SimplePotentiometer::setSectors(uint16_t newSectors){

	sectors = (newSectors > MAX_SECTORS) ?  MAX_SECTORS : newSectors;
	// sectors set to 0 change to 1 at least
	if(!sectors) sectors++;
}


#ifndef SIMPLEPOTENTIOMETER_H_
#define SIMPLEPOTENTIOMETER_H_

#include "ArduinoIOPins.h"
#define MAX_SECTORS 1024


class SimplePotentiometer : public AnalogInputPin{

	private :
		// Number of sectors in which analog input will be divided linearly.
		uint16_t sectors;
		// last known sector
		uint16_t _lastSector;
		// action to perform when sector changed.
		void (*sectorChangedAction)(uint16_t);
	public:

		void initPot(uint8_t potPin, uint16_t sectors = 2);

		SimplePotentiometer();
		virtual ~SimplePotentiometer();

		uint16_t lastSector();
		boolean sectorChanged();
		void setOnSectorChangedAction(void(*action)(uint16_t));
		void update();

		uint16_t getValue();
		uint16_t getSector();
		void setSectors(uint16_t sectors);




};

#endif /* SIMPLEPOTENTIOMETER_H_ */

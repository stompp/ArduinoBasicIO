#include <ArduinoBasicIO.h>
#define INPUT_PIN (A0)
#define LED 3

AnalogInputPin pot(INPUT_PIN);
DigitalOutputPin led(LED);

void setup(){

}

void loop(){

	led.writeAnalog(pot.readto8bit());

}

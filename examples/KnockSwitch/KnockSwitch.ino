#include <KnockSwitch.h>

#define SWITCH A5
#define SWITCH_ON HIGH
#define ACTUATOR 6
#define ACTUATOR_ON HIGH
#define ON_KNOCKS 2
#define OFF_KNOCKS 3

KnockSwitch knock;

void setup(){
  Serial.begin(9600);
  Serial.println("Iniciado!");
  knock.init(SWITCH,SWITCH_ON,ACTUATOR,ACTUATOR_ON);
  knock.setKnocks(ON_KNOCKS,OFF_KNOCKS);

}


void loop(){
 
  if(knock.update()){
    Serial.print("SWITCH ");
    Serial.println(knock.isOn() ? "ON" : "OFF");
  }



}
  
 
  
  

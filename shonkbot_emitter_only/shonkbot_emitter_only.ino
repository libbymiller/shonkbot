
/*

Shonkbot with IR object detection and a bump-and-turn action for obstacle avoidance

See http://jarkman.co.uk/catalog/robots/shonkbot.htm for more details

Just the IR for an other bot finder

*/

#include "IRDetector.h"

#define  DO_LOGGING

#define PIEZO_PIN 12                        // Wire a piezo sounder from pin 12 to ground
#define OTHER_BOT_PHOTOTRANSISTOR_PIN A0    // Wire IR phototransistor from A0 to ground, with a 10k pullup

#define LED_PIN 13                // Wire IR LED from pin 13 to ground 
#define SWARM_FREQUENCY 66
#define COLLISION_FREQUENCY 75

IRDetector swarmTransmitter(LED_PIN, -1, PIEZO_PIN, SWARM_FREQUENCY);


void setup()
{  
  #ifdef DO_LOGGING
  Serial.begin (57600); // for debugging

  Serial.print ("setup\n");
  #endif
  
  swarmTransmitter.setup();

}


void loop()
{
  swarmTransmitter.loop();
}




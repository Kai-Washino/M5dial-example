#include "M5Dial.h"
#include <M5UnitSynth.h>

M5UnitSynth synth;

int VOLUME = 40;  
int CHANNEL = 29;

unsigned long lastTime = 0;
unsigned long interval = 300; 

void setup() {
    M5.begin();
    Serial.begin(115200);    
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, 15, 13);
   synth.setInstrument(CHANNEL, 29, OverdrivenGuitar); 
}


void loop() {
    synth.setNoteOn(CHANNEL, 43, VOLUME);
    delay(500);
    synth.setNoteOff(CHANNEL, 43, VOLUME);
    delay(100);
    delay(2000);
}
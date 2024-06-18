#include "M5Dial.h"
#include <M5UnitSynth.h>

M5UnitSynth synth;

int VOLUME = 40;  

unsigned long lastTime = 0;
unsigned long interval = 300; 

void setup() {
    M5.begin();
    Serial.begin(115200);    
    
    // Synthの初期化
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, 15, 13);
    
    // チャンネル0にピアノを設定
   synth.setInstrument(0, 0, GrandPiano_1); // チャンネル0にピアノ
}


void loop() {
    synth.setNoteOn(0, 88, VOLUME);
    delay(100);
    synth.setNoteOff(0, 88, VOLUME);
    synth.setNoteOn(0, 84, VOLUME);
    delay(100);
    synth.setNoteOff(0, 84, VOLUME);
    delay(50);
    synth.setNoteOn(0, 88, VOLUME);
    delay(100);
    synth.setNoteOff(0, 88, VOLUME);
    synth.setNoteOn(0, 84, VOLUME);
    delay(100);
    synth.setNoteOff(0, 84, VOLUME);
    delay(50);
    synth.setNoteOn(0, 88, VOLUME);
    delay(100);
    synth.setNoteOff(0, 88, VOLUME);
    synth.setNoteOn(0, 84, VOLUME);
    delay(100);
    synth.setNoteOff(0, 84, VOLUME);
    delay(50);
    delay(2000);
}
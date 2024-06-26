#include "M5Dial.h"
#include "M5UnitSynth.h"
#include <Adafruit_NeoPixel.h>

#define PIN 2
#define NUM_LEDS 48
#define VOLUME  100
#define TEMPO_DELAY  150

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
M5UnitSynth synth;

void red(){
    for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
    }
    strip.show();
}

void black(){
    for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();
}


void setup() {
    Serial.begin(115200);
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, 15, 13);
    synth.setInstrument(0, 9, SynthDrum);  // synth drum
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    synth.setNoteOn(9, 36, VOLUME);
    synth.setNoteOn(9, 42, VOLUME);
    red();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 42, VOLUME);
    black();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 38, VOLUME);
    synth.setNoteOn(9, 42, VOLUME);
    red();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 42, VOLUME);
    black();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 36, VOLUME);
    synth.setNoteOn(9, 42, VOLUME);
    red();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 36, VOLUME);
    synth.setNoteOn(9, 42, VOLUME);
    black();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 38, VOLUME);
    synth.setNoteOn(9, 42, VOLUME);
    red();
    delay(TEMPO_DELAY);

    synth.setNoteOn(9, 42, VOLUME);
    black();
    delay(TEMPO_DELAY);
}
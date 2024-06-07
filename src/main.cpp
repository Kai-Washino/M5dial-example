#include "M5Dial.h"
#include <Adafruit_NeoPixel.h>

#define CARD1 "44073ba2d5980"
#define PIN 2
#define NUM_LEDS 48

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, true);
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);    
    M5Dial.Display.setTextSize(3);
    strip.begin();
    strip.show();
}

long oldPosition = -999;

void loop() {
    M5Dial.update();
    long newPosition = M5Dial.Encoder.read();
    if (newPosition != oldPosition) {
        M5Dial.Speaker.tone(8000, 20);
        M5Dial.Display.clear();
        oldPosition = newPosition;        
        M5Dial.Display.drawString(String(newPosition),
                                  M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);
    }
    if (M5Dial.BtnA.wasPressed()) {
        M5Dial.Encoder.readAndReset();
    }
    if (M5Dial.BtnA.pressedFor(5000)) {
        M5Dial.Encoder.write(100);
    }

    if (M5Dial.Rfid.PICC_IsNewCardPresent() &&
        M5Dial.Rfid.PICC_ReadCardSerial()) {
        M5Dial.Display.clear();        

        String uid = "";
        for (byte i = 0; i < M5Dial.Rfid.uid.size;
             i++) {            
            uid += String(M5Dial.Rfid.uid.uidByte[i], HEX);
        }
        if (uid == CARD1  && newPosition == 0){
            M5Dial.Speaker.tone(8000, 20);
            M5Dial.Display.drawString("Correct", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);
            for(int i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(0, 0, 255));
            }
            strip.show();
        }
        else {
            M5Dial.Speaker.tone(20000, 40);
            M5Dial.Display.drawString("False", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);  
            for(int i=0; i<strip.numPixels(); i++) {
                strip.setPixelColor(i, strip.Color(255, 0, 0));
            }
            strip.show();
        }
    }
}
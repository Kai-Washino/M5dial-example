#include "M5Dial.h"
#define CARD1 "44073ba2d5980"

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, false, true);
    M5Dial.Display.setTextColor(GREEN);
    M5Dial.Display.setTextDatum(middle_center);    
    M5Dial.Display.setTextSize(1);
    M5Dial.Display.drawString("RFID Card", M5Dial.Display.width() / 2,
                              M5Dial.Display.height() / 2);
}

void loop() {
    if (M5Dial.Rfid.PICC_IsNewCardPresent() &&
        M5Dial.Rfid.PICC_ReadCardSerial()) {
        M5Dial.Display.clear();        

        String uid = "";
        for (byte i = 0; i < M5Dial.Rfid.uid.size;
             i++) {            
            uid += String(M5Dial.Rfid.uid.uidByte[i], HEX);
        }
        if (uid != CARD1){
            M5Dial.Speaker.tone(8000, 20);
            M5Dial.Display.drawString("Correct", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);        
        }
        else {
            M5Dial.Speaker.tone(20000, 40);
            M5Dial.Display.drawString("False", M5Dial.Display.width() / 2,
                                  M5Dial.Display.height() / 2);  

        }
    }
}
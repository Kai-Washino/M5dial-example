#include "M5Dial.h"
#include <M5UnitSynth.h>

M5UnitSynth synth;

int VOLUME = 20;  

unsigned long lastTime = 0;
unsigned long interval = 300; 

void setup() {
    M5.begin();
    Serial.begin(115200);    
    
    // Synthの初期化
    synth.begin(&Serial2, UNIT_SYNTH_BAUD, 15, 13);
    
    // チャンネル0にピアノを設定
   synth.setInstrument(0, 0, GrandPiano_1); // チャンネル0にピアノ
    synth.setInstrument(1, 24, AcGuitarNylon); // チャンネル1にアコースティックギター
    synth.setInstrument(9, 118, SynthDrum); // チャンネル9にシンセドラム（一般的にパーカッションはチャンネル9または10を使用）

}

void playChord(uint8_t channel, uint8_t note, uint8_t velocity) {
    synth.setNoteOn(channel, note, velocity);
    synth.setNoteOn(channel, note + 4, velocity);
    synth.setNoteOn(channel, note + 7, velocity);
}

void stopChord(uint8_t channel, uint8_t note, uint8_t velocity) {
    synth.setNoteOff(channel, note, velocity);
    synth.setNoteOff(channel, note + 4, velocity);
    synth.setNoteOff(channel, note + 7, velocity);
}

void playPianoPattern(int eightNote) {
    switch(eightNote) {
        case 0:
            playChord(0, 60, VOLUME); // Cメジャーコード
            break;
        case 1:
            stopChord(0, 60, VOLUME);
            break;
        case 2:
            playChord(0, 62, VOLUME); // Dマイナーコード
            break;
        case 3:
            stopChord(0, 62, VOLUME);
            break;
        case 4:
            playChord(0, 64, VOLUME); // Eマイナーコード
            break;
        case 5:
            stopChord(0, 64, VOLUME);
            break;
        case 6:
            playChord(0, 65, VOLUME); // Fメジャーコード
            break;
        case 7:
            stopChord(0, 65, VOLUME);
            break;
        case 8:
            playChord(0, 67, VOLUME); // Gメジャーコード
            break;
        case 9:
            stopChord(0, 67, VOLUME);
            break;
        case 10:
            playChord(0, 69, VOLUME); // Aマイナーコード
            break;
        case 11:
            stopChord(0, 69, VOLUME);
            break;
        case 12:
            playChord(0, 71, VOLUME); // Bディミニッシュコード
            break;
        case 13:
            stopChord(0, 71, VOLUME);
            break;
        case 14:
            playChord(0, 72, VOLUME); // Cメジャーコード（1オクターブ上）
            break;
        case 15:
            stopChord(0, 72, VOLUME);
            break;
        default:
            break;
    }
}

void playGuitarPattern(int eightNote) {
    switch(eightNote % 4) {
        case 0:
            synth.setNoteOn(1, 52, VOLUME); // E2
            synth.setNoteOn(1, 55, VOLUME); // G2
            synth.setNoteOn(1, 59, VOLUME); // B2
            break;
        case 1:
            synth.setNoteOff(1, 52, VOLUME);
            synth.setNoteOff(1, 55, VOLUME);
            synth.setNoteOff(1, 59, VOLUME);
            break;
        case 2:
            synth.setNoteOn(1, 57, VOLUME); // A2
            synth.setNoteOn(1, 60, VOLUME); // C3
            synth.setNoteOn(1, 64, VOLUME); // E3
            break;
        case 3:
            synth.setNoteOff(1, 57, VOLUME);
            synth.setNoteOff(1, 60, VOLUME);
            synth.setNoteOff(1, 64, VOLUME);
            break;
        default:
            break;
    }
}

void playDrumPattern(int eightNote) {
    switch(eightNote % 8){
        case 0:
            synth.setNoteOn(9, 36, VOLUME); // バスドラム
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 1:
            synth.setNoteOff(9, 36, VOLUME);
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 2:
            synth.setNoteOn(9, 38, VOLUME); // スネアドラム
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 3:
            synth.setNoteOff(9, 38, VOLUME);
            synth.setNoteOn(9, 46, VOLUME); // オープンハイハット
            break;
        case 4:
            synth.setNoteOn(9, 36, VOLUME); // バスドラム
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 5:
            synth.setNoteOff(9, 36, VOLUME);
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 6:
            synth.setNoteOn(9, 38, VOLUME); // スネアドラム
            synth.setNoteOn(9, 42, VOLUME); // ハイハット
            break;
        case 7:
            synth.setNoteOff(9, 38, VOLUME);
            synth.setNoteOn(9, 46, VOLUME); // オープンハイハット
            break;
        default:
            break;
    }
}

void loop() {
    static int eightNote = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastTime >= interval) {
        lastTime = currentTime;
        playPianoPattern(eightNote);
        playGuitarPattern(eightNote);
        playDrumPattern(eightNote);        
        eightNote = (eightNote + 1) % 16;
    }
}
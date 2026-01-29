#include "buzzer.h"
#include "pins_and_structs.h"
#include <Arduino.h>

unsigned long buzzerLastTime = 0;
unsigned long freqTime = 0;
unsigned long freqTimeStart = 0;
uint buzzerState = 1;
unsigned long buzzerDelayUs = 1;

// buzzerDelayUs = 600; // 840 Hz
// buzzerDelayUs = 500; // 991 Hz
// buzzerDelayUs = 400; // 1280 Hz
// buzzerDelayUs = 300; // 1680 Hz
// buzzerDelayUs = 200; // 2500 hz
// buzzerDelayUs = 100; // 4900 Hz
// buzzerDelayUs = 50;  // 9900 Hz

void set_freq_time(unsigned long freq, unsigned long time_us){
  set_freq(freq);
  freqTime = time_us;
  freqTimeStart = micros();
}

void set_freq(unsigned long freq){
  buzzerDelayUs = 1000000UL / (2 * freq);;
}

void buzz_buzzer(void){
  if (micros() - buzzerLastTime >= buzzerDelayUs) {
    buzzerLastTime = micros();

    if (1 == buzzerState){
      digitalWrite(BUZZER, HIGH);
      buzzerState = 0;
    } else {
      digitalWrite(BUZZER, LOW);
      buzzerState = 1;
    }
  }
  if ((micros() > freqTimeStart + freqTime) && (0 != freqTime)){
    set_freq(1);
  }
}



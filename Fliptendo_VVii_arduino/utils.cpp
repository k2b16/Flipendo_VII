#include "utils.h"
#include "pins_and_structs.h"
#include <Arduino.h>
#include "buzzer.h"

unsigned long userLedLastTime = 0;
uint userLedState = 1;

void setup_pins(void){
  pinMode(USER_LED, OUTPUT);
  
  pinMode(COL_1, OUTPUT);
  pinMode(COL_2, OUTPUT);
  pinMode(COL_3, OUTPUT);
  pinMode(COL_4, OUTPUT);
  pinMode(COL_5, OUTPUT);
  pinMode(COL_6, OUTPUT);
  pinMode(COL_7, OUTPUT);
  pinMode(COL_8, OUTPUT);
  pinMode(COL_9, OUTPUT);
  pinMode(COL_10, OUTPUT);
  pinMode(COL_11, OUTPUT);
  pinMode(COL_12, OUTPUT);
  pinMode(COL_13, OUTPUT);
  pinMode(COL_14, OUTPUT);

  pinMode(not_OE, OUTPUT);
  pinMode(STCP, OUTPUT);
  pinMode(SHCP, OUTPUT);
  pinMode(not_MR, OUTPUT);
  pinMode(DS, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(JS_SW, INPUT_PULLUP);
}

void user_led_blink(void){
  if (millis() - userLedLastTime >= 500) {
    userLedLastTime = millis();

    if (1 == userLedState){
      digitalWrite(USER_LED, HIGH);
      userLedState = 0;
    } else {
      digitalWrite(USER_LED, LOW);
      userLedState = 1;
    }
  }
}

// !!!!!!!!!!! clanker generated code !!!!!!!!!!!!!!!! //
void wait_us(unsigned long durationUs) {
  unsigned long start = micros();
  while (micros() - start < durationUs) {
    buzz_buzzer();
  }
}
// !!!!!!!!!!! clanker generated code !!!!!!!!!!!!!!!! //

void read_buttons(buttons_st* buttons){
  int state;
  state = digitalRead(UP);
  buttons->up = state;
  state = digitalRead(DOWN);
  buttons->down = state;
  state = digitalRead(LEFT);
  buttons->left = state;
  state = digitalRead(RIGHT);
  buttons->right = state;
}

void read_joystick(joystick_st* joystick){
  joystick->rx = analogRead(JS_RX);
  joystick->ry = analogRead(JS_RY);
  joystick->sw = digitalRead(JS_SW);
}

void beep_bootup_sound(void){
  // !!!!!!!!!!! clanker generated code !!!!!!!!!!!!!!!! //
  // beep beep beep
  for (int i = 0; i < 3; i++) {
      set_freq(1000);
      wait_us(500000);
      set_freq(1);
      wait_us(360000);
  }

  // GO!
  set_freq(2000);
  wait_us(800000);
  set_freq(1);
  // !!!!!!!!!!! clanker generated code !!!!!!!!!!!!!!!! //
}

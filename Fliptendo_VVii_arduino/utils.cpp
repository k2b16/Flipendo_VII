#include "utils.h"
#include "pins_and_structs.h"
#include <Arduino.h>

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
    Serial.println("blink");

    if (1 == userLedState){
      digitalWrite(USER_LED, HIGH);
      userLedState = 0;
    } else {
      digitalWrite(USER_LED, LOW);
      userLedState = 1;
    }
  }
}

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

void read_joystick(void){
  joystick_st joystick;
  joystick.rx = analogRead(JS_RX);
  joystick.ry = analogRead(JS_RY);
  Serial.printf("RX: %d, RY: %d \n", joystick.rx, joystick.ry);

  int state = digitalRead(JS_SW);
  if (state == LOW) {
    Serial.println("joystick switch pressed");
  }
}

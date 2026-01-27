#include "utils.h"
#include "pins_and_structs.h"
#include <Arduino.h>

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



#ifndef PINS_AND_STRUCTS_H
#define PINS_AND_STRUCTS_H

#include "cstdint"

/* joystick */
typedef struct {
  uint16_t rx;
  uint16_t ry;
  uint8_t sw;
} joystick_st;

/* buttons */
typedef struct {
  int up;
  int down;
  int left;
  int right;
} buttons_st;

/* pins */
const int UP = 4; // UP = 19 (old pin)
const int DOWN = 6;
const int LEFT = 7;
const int RIGHT = 5;

const int JS_SW = 42;
const int JS_RY = 1;
const int JS_RX = 2;

const int USER_LED = 20;

const int COL_1 = 39;
const int COL_2 = 38;
const int COL_3 = 45;
const int COL_4 = 48;
const int COL_5 = 47;
const int COL_6 = 21;
const int COL_7 = 14;
const int COL_8 = 13;
const int COL_9 = 12;
const int COL_10 = 11;
const int COL_11 = 10;
const int COL_12 = 9;
const int COL_13 = 46;
const int COL_14 = 3;

const int not_OE = 8;
const int STCP = 18;
const int SHCP = 17;
const int not_MR = 16;
const int DS = 15;

const int BUZZER = 41;

#endif

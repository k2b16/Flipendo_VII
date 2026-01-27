/* YBG Fliptendo VVii */

#include "pins_and_structs.h"
#include "utils.h"

/* variables */
unsigned long userLedLastTime = 0;
uint userLedState = 1;

int rows[] = {
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
  LOW,
};

/* custom functions */
void user_led_blink(void){
  if (millis() - userLedLastTime >= 1000) {
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

void shift_out(int rows[]){
  uint32_t shift_reg_delayMicroseconds = 1;
  // set everything default
  digitalWrite(SHCP, LOW);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(not_MR, HIGH);
  digitalWrite(not_OE, HIGH);
  delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  delayMicroseconds(shift_reg_delayMicroseconds);
  
  // master reset
  digitalWrite(not_MR, LOW);
  digitalWrite(SHCP, LOW);
  delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(not_MR, HIGH);
  digitalWrite(SHCP, LOW);
  delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  delayMicroseconds(shift_reg_delayMicroseconds);

  // shift out rows data
  for (uint8_t i=0; i<16; i++){
    digitalWrite(DS, rows[i]);

    digitalWrite(SHCP, LOW);
    digitalWrite(STCP, HIGH);
    delayMicroseconds(shift_reg_delayMicroseconds);
    digitalWrite(SHCP, HIGH);
    digitalWrite(STCP, LOW);
    delayMicroseconds(shift_reg_delayMicroseconds);
  }

  digitalWrite(SHCP, LOW);
  digitalWrite(STCP, HIGH);
  digitalWrite(not_OE, LOW);
  delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  digitalWrite(STCP, LOW);
  delayMicroseconds(shift_reg_delayMicroseconds);
}

void set_columns_gnd(void){
  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);
  digitalWrite(COL_4, LOW);
  digitalWrite(COL_5, LOW);
  digitalWrite(COL_6, LOW);
  digitalWrite(COL_7, LOW);
  digitalWrite(COL_8, LOW);
  digitalWrite(COL_9, LOW);
  digitalWrite(COL_10, LOW);
  digitalWrite(COL_11, LOW);
  digitalWrite(COL_12, LOW);
  digitalWrite(COL_13, LOW);
  digitalWrite(COL_14, LOW);
}

void set_columns_12V(void){
  digitalWrite(COL_1, HIGH);
  digitalWrite(COL_2, HIGH);
  digitalWrite(COL_3, HIGH);
  digitalWrite(COL_4, HIGH);
  digitalWrite(COL_5, HIGH);
  digitalWrite(COL_6, HIGH);
  digitalWrite(COL_7, HIGH);
  digitalWrite(COL_8, HIGH);
  digitalWrite(COL_9, HIGH);
  digitalWrite(COL_10, HIGH);
  digitalWrite(COL_11, HIGH);
  digitalWrite(COL_12, HIGH);
  digitalWrite(COL_13, HIGH);
  digitalWrite(COL_14, HIGH);
}

void set_all_rows_nc(void){
  rows[0] = LOW; // ROW6_L
  rows[1] = HIGH; // ROW6_H
  rows[2] = LOW; // ROW7_L
  rows[3] = HIGH; // ROW7_H
  rows[4] = HIGH; // ROW5_H
  rows[5] = LOW; // ROW5_L
  rows[6] = HIGH; // ROW4_H
  rows[7] = LOW; // NC
  rows[8] = LOW; // ROW1_L
  rows[9] = HIGH; // ROW1_H
  rows[10] = LOW; // ROW2_L
  rows[11] = HIGH; // ROW2_H
  rows[12] = LOW; // ROW3_L
  rows[13] = HIGH; // ROW3_H
  rows[14] = LOW; // ROW4_L
  rows[15] = LOW; // NC
}

void set_row7_12V(void){
  rows[2] = HIGH; // ROW7_L
  rows[3] = HIGH; // ROW7_H
}

void set_row7_gnd(void){
  rows[2] = LOW; // ROW7_L
  rows[3] = LOW; // ROW7_H
}

void set_row6_12V(void){
  rows[0] = HIGH; // ROW6_L
  rows[1] = HIGH; // ROW6_H
}

void set_row6_gnd(void){
  rows[0] = LOW; // ROW6_L
  rows[1] = LOW; // ROW6_H
}

void set_row5_12V(void){
  rows[4] = HIGH; // ROW5_H
  rows[5] = HIGH; // ROW5_L
}

void set_row5_gnd(void){
  rows[4] = LOW; // ROW5_H
  rows[5] = LOW; // ROW5_L
}

/* main setup function */
void setup() {
  setup_pins();

  set_columns_gnd();

  set_all_rows_nc();
  shift_out(rows);

  Serial.begin(115200);
  delay(500);
  Serial.println("ESP32-S3 started");
}

uint32_t pulse_us = 300;

void black_3x3(void){
  set_all_rows_nc();
  set_row7_12V();
  shift_out(rows);
  digitalWrite(COL_1, HIGH);
  digitalWrite(COL_2, HIGH);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, HIGH);

  digitalWrite(COL_2, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, HIGH);

  digitalWrite(COL_3, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_12V();
  shift_out(rows);
  digitalWrite(COL_1, HIGH);
  digitalWrite(COL_2, HIGH);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, HIGH);

  digitalWrite(COL_2, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, HIGH);

  digitalWrite(COL_3, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_12V();
  shift_out(rows);
  digitalWrite(COL_1, HIGH);
  digitalWrite(COL_2, HIGH);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, HIGH);

  digitalWrite(COL_2, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, HIGH);

  digitalWrite(COL_3, LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, HIGH);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3_row6_col3(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3_row6_col3_row5_col3(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3_row6_col3_row5_col3_col2(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);

  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col3_row6_col3_row5_col3_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row7_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
 
  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row6_col3_row5_col3_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row5_col3_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_3, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);

  digitalWrite(COL_3, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_3, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row5_col2_col1_row6_col1(void){
  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_2, LOW);
  digitalWrite(COL_1, LOW);
  
  digitalWrite(COL_2, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_2, LOW);
   
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row5_col1_row6_col1(void){
  set_all_rows_nc();
  set_row5_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);
  
  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row6_col1(void){
  set_all_rows_nc();
  set_row6_gnd();
  shift_out(rows);

  digitalWrite(COL_1, LOW);

  digitalWrite(COL_1, HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COL_1, LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

uint32_t delay_ms = 50;

/* main loop function */
void loop() {
  black_3x3();
  white_row7_col1();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3_row6_col3();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3_row6_col3_row5_col3();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3_row6_col3_row5_col3_col2();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1();
  delay(delay_ms);

  black_3x3();
  white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row7_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row7_col3_row6_col3_row5_col3_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row6_col3_row5_col3_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row5_col3_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row5_col2_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row5_col1_row6_col1();
  delay(delay_ms);

  black_3x3();
  white_row6_col1();
  delay(delay_ms);

  black_3x3();
  delay(delay_ms);

  /*
  user_led_blink();

  buttons_st buttons;
  read_buttons(&buttons);
  if (LOW == buttons.up){
    Serial.println("up pressed");
    black_3x3();
    white_row5_col1_col2();
  }
  if (LOW == buttons.down){
    Serial.println("down pressed");
    black_3x3();
    white_row5_col3();
  }
  if (LOW == buttons.left){
    Serial.println("left pressed");
    black_3x3();
    white_row6_col2();
  }
  if (LOW == buttons.right){
    Serial.println("right pressed");
    black_3x3();
    white_row7_col1();
  }
  delay(100);
  */
  //read_joystick();
}

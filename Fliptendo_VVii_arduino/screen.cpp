#include "screen.h"
#include "pins_and_structs.h"
#include <Arduino.h>

uint32_t pulse_us = 1100;
uint8_t matrix[7][14] = {0};

void set_matrix_row_column(uint8_t row, uint8_t col){
  matrix[row-1][col-1] = 1;
}

void clear_matrix_row_column(uint8_t row, uint8_t col){
  matrix[row-1][col-1] = 0;
}

void clear_matrix(void){
  for (uint8_t row = 1; row < 8; row++){
    for (uint8_t column = 1; column < 15; column++){
      matrix[row-1][column-1] = 0;
    }
  }
}

void draw_matrix(void){
  for (uint8_t row = 1; row < 8; row++){
    for (uint8_t column = 1; column < 15; column++){
      if (matrix[row-1][column-1])
        white_row_col(row, column);
    }
  }
}


const int COLUMNS[] = {
  0, // unused
  COL_1,
  COL_2,
  COL_3,
  COL_4,
  COL_5,
  COL_6,
  COL_7,
  COL_8,
  COL_9,
  COL_10,
  COL_11,
  COL_12,
  COL_13,
  COL_14
};

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

const uint8_t ROW1_L = 8;
const uint8_t ROW1_H = 9;
const uint8_t ROW2_L = 10;
const uint8_t ROW2_H = 11;
const uint8_t ROW3_L = 12;
const uint8_t ROW3_H = 13;
const uint8_t ROW4_L = 14;
const uint8_t ROW4_H = 6;
const uint8_t ROW5_L = 5;
const uint8_t ROW5_H = 4;
const uint8_t ROW6_L = 0;
const uint8_t ROW6_H = 1;
const uint8_t ROW7_L = 2;
const uint8_t ROW7_H = 3;

const uint8_t ROWS_H[] = {
  0, // unused
  ROW1_H,
  ROW2_H,
  ROW3_H,
  ROW4_H,
  ROW5_H,
  ROW6_H,
  ROW7_H
};

const uint8_t ROWS_L[] = {
  0, // unused
  ROW1_L,
  ROW2_L,
  ROW3_L,
  ROW4_L,
  ROW5_L,
  ROW6_L,
  ROW7_L
};

void set_12V_on_row(uint8_t row){
  rows[ROWS_L[row]] = HIGH; // ROW7_L
  rows[ROWS_H[row]] = HIGH; // ROW7_H
}

void set_gnd_on_row(uint8_t row){
  rows[ROWS_L[row]] = LOW; // ROW7_L
  rows[ROWS_H[row]] = LOW; // ROW7_H
}

void shift_out_all_rows_nc(void){
  set_all_rows_nc();
  shift_out(rows);
}

void shift_out(int rows[]){
  uint32_t shift_reg_delayMicroseconds = 1;

  // set everything default
  digitalWrite(SHCP, LOW);
  digitalWrite(DS, LOW);
  digitalWrite(STCP, LOW);
  digitalWrite(not_MR, HIGH);
  digitalWrite(not_OE, HIGH);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  
  // master reset
  digitalWrite(not_MR, LOW);
  digitalWrite(SHCP, LOW);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(not_MR, HIGH);
  digitalWrite(SHCP, LOW);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  //delayMicroseconds(shift_reg_delayMicroseconds);

  // shift out rows data
  for (uint8_t i=0; i<16; i++){
    digitalWrite(DS, rows[i]);

    digitalWrite(SHCP, LOW);
    digitalWrite(STCP, HIGH);
    //delayMicroseconds(shift_reg_delayMicroseconds);
    digitalWrite(SHCP, HIGH);
    digitalWrite(STCP, LOW);
    //delayMicroseconds(shift_reg_delayMicroseconds);
  }
  
  // shift final and output enable
  digitalWrite(SHCP, LOW);
  digitalWrite(STCP, HIGH);
  digitalWrite(not_OE, LOW);
  //delayMicroseconds(shift_reg_delayMicroseconds);
  digitalWrite(SHCP, HIGH);
  digitalWrite(STCP, LOW);
  //delayMicroseconds(shift_reg_delayMicroseconds);
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

void clear_screen(void){
  for (uint8_t row = 1; row < 8; row++){
    set_all_rows_nc();
    set_12V_on_row(row);
    shift_out(rows);
    for (uint8_t column = 1; column < 15; column++){
      digitalWrite(COLUMNS[column], HIGH);
    }
    for (uint8_t column = 1; column < 15; column++){
      digitalWrite(COLUMNS[column], LOW);
      delayMicroseconds(pulse_us);
      digitalWrite(COLUMNS[column], HIGH);
    }
    for (uint8_t column = 1; column < 15; column++){
      digitalWrite(COLUMNS[column], LOW);
    }
    set_all_rows_nc();
    shift_out(rows);
  }
}

void black_3x3(void){
  set_all_rows_nc();
  set_12V_on_row(7);
  shift_out(rows);
  digitalWrite(COLUMNS[1], HIGH);
  digitalWrite(COLUMNS[2], HIGH);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[1], HIGH);

  digitalWrite(COLUMNS[2], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[2], HIGH);

  digitalWrite(COLUMNS[3], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  digitalWrite(COLUMNS[2], LOW);
  digitalWrite(COLUMNS[3], LOW);

  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_12V_on_row(6);
  shift_out(rows);
  digitalWrite(COLUMNS[1], HIGH);
  digitalWrite(COLUMNS[2], HIGH);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[1], HIGH);

  digitalWrite(COLUMNS[2], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[2], HIGH);

  digitalWrite(COLUMNS[3], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  digitalWrite(COLUMNS[2], LOW);
  digitalWrite(COLUMNS[3], LOW);

  set_all_rows_nc();
  shift_out(rows);

  set_all_rows_nc();
  set_12V_on_row(5);
  shift_out(rows);
  digitalWrite(COLUMNS[1], HIGH);
  digitalWrite(COLUMNS[2], HIGH);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[1], HIGH);

  digitalWrite(COLUMNS[2], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[2], HIGH);

  digitalWrite(COLUMNS[3], LOW);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[3], HIGH);

  digitalWrite(COLUMNS[1], LOW);
  digitalWrite(COLUMNS[2], LOW);
  digitalWrite(COLUMNS[3], LOW);

  set_all_rows_nc();
  shift_out(rows);
}

void white_row_col(uint8_t row, uint8_t col){
  set_all_rows_nc();
  set_gnd_on_row(row);
  shift_out(rows);

  digitalWrite(COLUMNS[col], LOW);

  digitalWrite(COLUMNS[col], HIGH);
  delayMicroseconds(pulse_us);
  digitalWrite(COLUMNS[col], LOW);
  
  set_all_rows_nc();
  shift_out(rows);
}

void white_row7_col1(void){
  set_all_rows_nc();
  set_gnd_on_row(7);
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
  set_gnd_on_row(7);
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
  set_gnd_on_row(7);
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

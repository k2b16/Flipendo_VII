#include "game.h"
#include "buzzer.h"
#include "pins_and_structs.h"
#include "utils.h"
#include "screen.h"
#include <Arduino.h>

/*
clear_screen();
clear_matrix();
set_matrix_row_column(1, 1);
draw_matrix();
set_freq_time(1000, 50000);
*/

uint8_t rand_array[100] = {
    2, 0, 3, 1, 2, 0, 1, 3, 0, 2,
    1, 1, 0, 2, 3, 0, 1, 2, 3, 0,
    2, 3, 1, 0, 2, 3, 1, 0, 0, 1,
    3, 2, 0, 1, 2, 3, 1, 0, 2, 1,
    0, 3, 2, 1, 0, 3, 2, 0, 1, 3,
    2, 0, 1, 3, 2, 1, 0, 3, 2, 1,
    0, 3, 1, 2, 0, 1, 3, 2, 0, 1,
    3, 2, 0, 1, 3, 0, 2, 1, 3, 0,
    1, 2, 3, 0, 1, 2, 3, 0, 2, 1,
    0, 3, 2, 1, 0, 3, 1, 2, 0, 1
};

uint8_t rand_counter = 0;

uint8_t x_pos = 14;
uint8_t y_pos = 2;

uint16_t js_buffer = 300;
const uint16_t js_x_mid = 2010;
const uint16_t js_y_mid = 1960;

uint8_t check_js(joystick_st* joystick){
  if (joystick->rx > js_x_mid + js_buffer){
    Serial.println("joystick right");
    return 3;
  } else if (joystick->rx < js_x_mid - js_buffer){
    Serial.println("joystick left");
    return 2;
  }

  if (joystick->ry < js_y_mid - js_buffer){
    Serial.println("joystick up");
    return 0;
  } else if (joystick->ry > js_y_mid + js_buffer){
    Serial.println("joystick down");
    return 1;
  }
}

uint8_t arrows[4][5][5] = {
  {{0,0,1,0,0},
  {0,0,1,0,0},
  {1,1,1,1,1},
  {0,1,1,1,0},
  {0,0,1,0,0}},
  {{0,0,1,0,0},
  {0,1,1,1,0},
  {1,1,1,1,1},
  {0,0,1,0,0},
  {0,0,1,0,0}},
  {{0,0,1,0,0},
  {0,1,1,0,0},
  {1,1,1,1,1},
  {0,1,1,0,0},
  {0,0,1,0,0}},
  {{0,0,1,0,0},
  {0,0,1,1,0},
  {1,1,1,1,1},
  {0,0,1,1,0},
  {0,0,1,0,0}}
};

void draw_arrow(uint8_t arrow, uint8_t x, uint8_t y){
  clear_screen();
  clear_matrix();

  for (uint8_t i = 0; i < 5; i++){
    for (uint8_t j = 0; j < 5; j++){
      if (arrows[arrow][i][j]){
        if ((x+i < 15) && (y+j < 8))
          set_matrix_row_column(y+j, x+i);
      }
    }
  }

  draw_matrix();
}

void draw_animation(void){
  clear_screen();
  clear_matrix();

  for (uint8_t i = 1; i < 8; i++){
    for (uint8_t j = 1; j < 15; j++){
      set_matrix_row_column(i, j);
    }
  }
  draw_matrix();
}

uint8_t cat_animation = 1;

void draw_cat(void){
  clear_screen();
  clear_matrix();

  for (uint8_t i = cat_animation; i < 8; i++){
    for (uint8_t j = 1; j < 15; j++){
      set_matrix_row_column(i, j);
    }
  }
  cat_animation++;
  if (cat_animation > 7)
    cat_animation = 1;

  draw_matrix();
}

uint8_t heart[7][14] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,1,1,0,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,1,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0}
};

void draw_heart(void){
  clear_screen();
  clear_matrix();

  for (uint8_t i = 1; i < 8; i++){
    for (uint8_t j = 1; j < 15; j++){
      if (heart[i-1][j-1])
        set_matrix_row_column(i, j);
    }
  }
  draw_matrix();
}

const uint8_t smiley[7][14] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,1,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,1,0,0,0,0},
    {0,1,1,0,0,0,0,0,0,0,0,1,1,0},
    {0,0,1,1,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,1,1,1,1,1,1,1,1,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0,0,0,0},
};

void draw_smiley(void){
  clear_screen();
  clear_matrix();

  for (uint8_t i = 1; i < 8; i++){
    for (uint8_t j = 1; j < 15; j++){
      if (smiley[i-1][j-1])
        set_matrix_row_column(i, j);
    }
  }
  draw_matrix();
}

void scroll_arrow(joystick_st* joystick, buttons_st* buttons){
  draw_arrow(rand_array[rand_counter], x_pos, y_pos);
  x_pos--;
  if (x_pos < 1){
    x_pos = 14;
    rand_counter++;
    if (rand_counter > 99)
      rand_counter = 0;
  }

  if (1==x_pos){
    if (0 == rand_array[rand_counter]){ // right
      if ((LOW == buttons->right) && (3 == check_js(joystick))){
        draw_animation();
        x_pos = 14;
        rand_counter++;
        if (rand_counter > 99)
          rand_counter = 0;
      }    
    }
    else if (1 == rand_array[rand_counter]){ // left
      if ((LOW == buttons->left) && (2 == check_js(joystick))){
        draw_animation();
        x_pos = 14;
        rand_counter++;
        if (rand_counter > 99)
          rand_counter = 0;
      }    
    }
    else if (2 == rand_array[rand_counter]){ // down
      if ((LOW == buttons->down) && (1 == check_js(joystick))){
        draw_animation();
        x_pos = 14;
        rand_counter++;
        if (rand_counter > 99)
          rand_counter = 0;
      }    
    }
    else if (3 == rand_array[rand_counter]){ // up
      if ((LOW == buttons->up) && (0 == check_js(joystick))){
        draw_animation();
        x_pos = 14;
        rand_counter++;
        if (rand_counter > 99)
          rand_counter = 0;
      }    
    }
  }
}

uint8_t gameState = 0;


void game(void){
  if (0 == gameState){
    // read buttons
    buttons_st buttons;
    read_buttons(&buttons);
    if (LOW == buttons.up){
      Serial.println("up pressed");
    }
    if (LOW == buttons.down){
      Serial.println("down pressed");
    }
    if (LOW == buttons.left){
      Serial.println("left pressed");
    }
    if (LOW == buttons.right){
      Serial.println("right pressed");
    }
    
    // read joystick
    joystick_st joystick;
    read_joystick(&joystick);
    if (LOW == joystick.sw) {
      Serial.println("joystick switch pressed");
      gameState = 1;
    }
    scroll_arrow(&joystick, &buttons);
  }
  else if (1 == gameState){
    // read buttons
    buttons_st buttons;
    read_buttons(&buttons);
    if (LOW == buttons.up){
      Serial.println("up pressed");
      draw_animation();
    }
    if (LOW == buttons.down){
      Serial.println("down pressed");
      draw_cat();
    }
    if (LOW == buttons.left){
      Serial.println("left pressed");
      draw_heart();
    }
    if (LOW == buttons.right){
      Serial.println("right pressed");
      draw_smiley();
    }
    
    joystick_st joystick;
    read_joystick(&joystick);
    if (LOW == joystick.sw) {
      Serial.println("joystick switch pressed");
      gameState = 0;
    }
  }
}



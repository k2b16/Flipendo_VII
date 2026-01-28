#ifndef UTILS_H
#define UTILS_H

#include "pins_and_structs.h"

void setup_pins(void);
void user_led_blink(void);
void read_buttons(buttons_st* buttons);
void read_joystick(void);

#endif



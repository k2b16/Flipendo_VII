#ifndef BUZZER_H
#define BUZZER_H

#include "cstdint"

void buzz_buzzer(void);
void set_freq(unsigned long freq);
void set_freq_time(unsigned long freq, unsigned long time_us);

#endif

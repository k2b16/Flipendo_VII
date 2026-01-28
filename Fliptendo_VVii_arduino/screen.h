#ifndef SCREEN_H
#define SCREEN_H

#include "cstdint"

void shift_out_all_rows_nc(void);
void shift_out(int rows[]);
void set_columns_gnd(void);
void set_columns_12V(void);
void set_all_rows_nc(void);
void set_row7_12V(void);
void set_row7_gnd(void);
void set_row6_12V(void);
void set_row6_gnd(void);
void set_row5_12V(void);
void set_row5_gnd(void);

void set_matrix_row_column(uint8_t row, uint8_t col);
void clear_matrix_row_column(uint8_t row, uint8_t col);
void clear_matrix(void);

void clear_screen(void);
void white_row_col(uint8_t row, uint8_t col);
void draw_matrix(void);

void black_3x3(void);
void white_row7_col1(void);
void white_row7_col1_col2(void);
void white_row7_col1_col2_col3(void);
void white_row7_col1_col2_col3_row6_col3(void);
void white_row7_col1_col2_col3_row6_col3_row5_col3(void);
void white_row7_col1_col2_col3_row6_col3_row5_col3_col2(void);
void white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1(void);
void white_row7_col1_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1(void);
void white_row7_col2_col3_row6_col3_row5_col3_col2_col1_row6_col1(void);
void white_row7_col3_row6_col3_row5_col3_col2_col1_row6_col1(void);
void white_row6_col3_row5_col3_col2_col1_row6_col1(void);
void white_row5_col3_col2_col1_row6_col1(void);
void white_row5_col2_col1_row6_col1(void);
void white_row5_col1_row6_col1(void);
void white_row6_col1(void);

#endif


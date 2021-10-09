/*
 * matrix_display.h
 *
 *  Created on: Oct 2, 2021
 *      Author: PC
 */

#ifndef INC_MATRIX_DISPLAY_H_
#define INC_MATRIX_DISPLAY_H_

//number of rows and cols
const int MAX_LED_MATRIX = 8;
//bit check for letter 'A' to display on SEGMENT
uint8_t matrix_buffer[8] = {0x00,0x18,0x24,0x42,0x42,0x42,0x7e,0x42};
//int led_matrix_index = 0;

void updateLEDMatrix(int index);
void bitCheckOnRow(int index);
void clearAllMatrix(void );
void displayLEDMatrix(void );
void matrixAnimation(void );
#endif /* INC_MATRIX_DISPLAY_H_ */

/*
 * segment_display.h
 *
 *  Created on: Sep 13, 2021
 *      Author: PC
 */

#ifndef INC_SEGMENT_DISPLAY_H_
#define INC_SEGMENT_DISPLAY_H_




uint8_t update_value_segment(uint8_t value, int idx);
void display_segment_number(int idx);
void update7SEG(int index);
void updateClockBuffer(int hour, int minute);
#endif /* INC_SEGMENT_DISPLAY_H_ */

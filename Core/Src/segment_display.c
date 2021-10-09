/*
 * display_segment.c
 *
 *  Created on: Sep 13, 2021
 *      Author: PC
 */
#include "main.h"
#include "segment_display.h"


//Maximum number of digits
#define NUMBER_OF_DECIMAL_DIGITS 	10
#define NUMBER_OF_SEVEN_SEGMENTS	4

/*LED CONVERSION
 * A is least significant bit
 * G is the most significant bit
 * E.g: 0x3f= 0b0111111 => LED displays 0*/
static uint8_t sevenSegmentLEDConversion[NUMBER_OF_DECIMAL_DIGITS] = {0x3f, 0x6, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x7, 0x7F, 0x6F};

// Seven segments LEDs

//Buffer variable
//ACTUAL ARRAY FOR DISPLAYING
static uint8_t segmentBuffer[NUMBER_OF_SEVEN_SEGMENTS];


//update segmentBuffer
uint8_t update_value_segment(uint8_t value, int idx)
{
	 if(idx >= NUMBER_OF_SEVEN_SEGMENTS) return 0;
	 if (value > NUMBER_OF_DECIMAL_DIGITS) return 0;
	 segmentBuffer[idx] = value;
	 return 1;
}

//get signals from segmentbuffer then writepin accordingly
void display_segment_number(int idx){
	uint8_t temp = sevenSegmentLEDConversion[segmentBuffer[idx]];
	//AND WITH EACH BIT IN 7 STARTING BITS
	//A
	if(temp & 0x01){
		HAL_GPIO_WritePin(SEG0_GPIO_Port , SEG0_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG0_GPIO_Port , SEG0_Pin , 1);
	}
	//B
	if(temp & 0x02){
		HAL_GPIO_WritePin(SEG1_GPIO_Port , SEG1_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG1_GPIO_Port , SEG1_Pin , 1);
	}
	//C
	if(temp & 0x04){
		HAL_GPIO_WritePin(SEG2_GPIO_Port , SEG2_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG2_GPIO_Port , SEG2_Pin , 1);
	}
	//D
	if(temp & 0x08){
		HAL_GPIO_WritePin(SEG3_GPIO_Port , SEG3_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG3_GPIO_Port , SEG3_Pin , 1);
	}
	//E
	if(temp & 0x10){
		HAL_GPIO_WritePin(SEG4_GPIO_Port , SEG4_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG4_GPIO_Port , SEG4_Pin , 1);
	}
	//F
	if(temp & 0x20){
		HAL_GPIO_WritePin(SEG5_GPIO_Port , SEG5_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG5_GPIO_Port , SEG5_Pin , 1);
	}
	//G
	if(temp & 0x40){
		HAL_GPIO_WritePin(SEG6_GPIO_Port , SEG6_Pin , 0);
	} else{
		HAL_GPIO_WritePin(SEG6_GPIO_Port , SEG6_Pin , 1);
	}


}


//ARRAY FOR VALUES OF 4 LED
//THIS IS NOT THE ARRAY FOR DISPLAYING.
int led_buffer[4] = {1, 2, 3, 4};
int index_led = 0;
//update led_index and EN signals
void update7SEG(int index){
	switch(index){
		case 0:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			update_value_segment(led_buffer[index], index);
			display_segment_number(index);
			index_led = index;
			break;
		case 1:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			update_value_segment(led_buffer[index], index);
			display_segment_number(index);
			index_led = index;
			break;
		case 2:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);
			update_value_segment(led_buffer[index], index);
			display_segment_number(index);
			index_led = index;
			break;
		case 3:
			HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
			HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
			HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);
			HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);
			update_value_segment(led_buffer[index], index);
			display_segment_number(index);
			index_led = index;
			break;
		default:
			break;
	}
}

//update led_buffer
void updateClockBuffer(int hour, int minute){

	if(hour < 10){
		led_buffer[0]  = 0;
		led_buffer[1]  = hour;
	} else{
		led_buffer[0]  = hour/10;
		led_buffer[1]  = hour%10;
	}
	if(minute < 10){
		led_buffer[2]  = 0;
		led_buffer[3]  = minute;

	} else {
		led_buffer[2]  = minute/10;
		led_buffer[3]  = minute%10;
	}


}
//update second, minute,hour
//based on timer2_counter, display the appropriate 7SEGs, 250ms for each 7SEG
void displayClock(int hour, int minute, int second, int timer2_counter){
  	   	  if(second >= 60){
  	   		  second = 0;
  	   		  minute++;
  	   	  }
  	   	  if(minute >= 60){
  	   		  minute = 0;
  	   		  hour++;
  	   	  }
  	   	  if(hour >= 24){
  	   		  hour = 0;
  	   	  }
  	   	  updateClockBuffer(hour, minute);

  	   	  if(timer2_counter > 75) {
  	   		  update7SEG(0);

  	   	  }
  	   	  else if(timer2_counter > 50){
  	   		  update7SEG(1);
  	   	  }
  	   	  else if(timer2_counter > 25) {
  	   		  update7SEG(2);
  	   	  }
  	   	  else if(timer2_counter > 0) {
  	   		  update7SEG(3);

  	   	  }
}

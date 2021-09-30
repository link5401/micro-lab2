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
static uint8_t segmentBuffer[NUMBER_OF_SEVEN_SEGMENTS];

uint8_t update_value_segment(uint8_t value, int idx)
{
	 if(idx >= NUMBER_OF_SEVEN_SEGMENTS) return 0;
	 if (value > NUMBER_OF_DECIMAL_DIGITS) return 0;
	 segmentBuffer[idx] = value;
	 return 1;
}

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

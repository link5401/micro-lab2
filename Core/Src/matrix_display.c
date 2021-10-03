/*
 * matrix_display.c
 *
 *  Created on: Oct 2, 2021
 *      Author: PC
 */
#include "main.h"
#include "matrix_display.h"
const int MAX_LED_MATRIX = 8;
uint8_t matrix_buffer[8] = {0x00,0x18,0x24,0x42,0x42,0x42,0x7e,0x42};
int led_matrix_index = 0;



void displayLEDMatrix(int index){
	uint8_t temp = matrix_buffer[index];
	//col7
	if (temp & 0x01) HAL_GPIO_WritePin(COL7_GPIO_Port, COL7_Pin, 1);
	else HAL_GPIO_WritePin(COL7_GPIO_Port, COL7_Pin, 0);
	//col6
	if (temp & 0x02) HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, 1);
	else HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, 0);
	//col5
	if (temp & 0x04) HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, 1);
	else HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, 0);
	//col4
	if (temp & 0x08) HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, 1);
	else HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, 0);
	//col3
	if (temp & 0x10) HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, 1);
	else HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, 0);
	//col2
	if (temp & 0x20) HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, 1);
	else HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, 0);
	//col1
	if (temp & 0x40) HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, 1);
	else HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, 0);
	//col0
	if (temp & 0x80) HAL_GPIO_WritePin(COL0_GPIO_Port, COL0_Pin, 1);
	else HAL_GPIO_WritePin(COL0_GPIO_Port, COL0_Pin, 0);

}
void updateLEDMatrix(int index){
	switch(index){
		case 0:
			HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 1);

			break;
		case 1:
			HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 1);
			break;
		case 2:
			HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 1);
			break;
		case 3:
			HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 1);
			break;
		case 4:
			HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 1);
			break;
		case 5:
			HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 1);
			break;
		case 6:
			HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 1);
			break;
		case 7:
			HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 1);
			break;
		default:
			break;
	}
	displayLEDMatrix(index);

}
void clearAllMatrix(void ){
	HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, 0);
	HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, 0);
	HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, 0);
	HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, 0);
	HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, 0);
	HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, 0);
	HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, 0);
	HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, 0);

	HAL_GPIO_WritePin(COL0_GPIO_Port, COL0_Pin, 0);
	HAL_GPIO_WritePin(COL1_GPIO_Port, COL1_Pin, 0);
	HAL_GPIO_WritePin(COL2_GPIO_Port, COL2_Pin, 0);
	HAL_GPIO_WritePin(COL3_GPIO_Port, COL3_Pin, 0);
	HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, 0);
	HAL_GPIO_WritePin(COL5_GPIO_Port, COL5_Pin, 0);
	HAL_GPIO_WritePin(COL6_GPIO_Port, COL6_Pin, 0);
	HAL_GPIO_WritePin(COL7_GPIO_Port, COL7_Pin, 0);
}
void matrixAnimation(void){
	//circular shifting for each row
	int bitToShift = 1;
	for(int i = 0; i< MAX_LED_MATRIX; i++){
		matrix_buffer[i] = (matrix_buffer[i] >> bitToShift) | (matrix_buffer[i] << (MAX_LED_MATRIX - bitToShift));
	}
}

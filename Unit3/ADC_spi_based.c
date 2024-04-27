/* Question
The pin diagram shown in figure 5(b)(a) is TLV2541 IC, a high performance, 12-bit, low power, miniature, CMOS analog-to-digital Converter. 
The pin functions are listed as below.
CS- Chip Select, AIN- Analog Input, SCLK- Serial Clock, SDO- Serial Data Output, NC- No Connection.
The conversion procedure is as follows.
The falling edge of CS is the start of the cycle. The converter sample time is 12 SCLKs in duration, beginning on the 5thSCLK 
received after the converter has received a high-to-low CS transition. The conversion is started after the 16th SCLK falling edge and takes 3.5 μs to complete. The converted digital data is presented on SDO. The SDO data presented during a cycle is the result of the conversion of the sample taken during the previous cycle. The Timing diagram is shown in figure 5(b)(b).
Develop BSP (Board Support Package) to interface TLV2541 to 8051 MCU. Use SPI type of serial interface to connect TLV2541. S
how interfacing diagram. Write an application code to demonstrate analog to digital conversion.
/*


/*Solution
PA0 -> CS
PA ->1 SCLK
PA ->2 SDO
*/
#include "main.h"
uint16_t read_adc_value();

int main(){
	while(1){
		uint16_t data =read_adc_value();
		HAL_DELAY(1);
	}
}
	

uint16_t read_adc_value(){
	uint 16_t adcout;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN0, GPIO_PIN_RESET); //cs pin low
	for (nt i = 0; i<12; i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN1, GPIO_PIN_SET); //SCLK pin
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN1, GPIO_PIN_RESET); //SCLK pin
		adcout = HAL_GPIO_ReadPIN( GPIOA , GPIO_PIN2)<<(12-i);//adc value read
	}
	
	for (int i = 0; i<4; i++){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN1, GPIO_PIN_SET); //SCLK pin
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN1, GPIO_PIN_RESET); //SCLK pin
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN0, GPIO_PIN_SET); //cs pin High
	return adcout;
}

#include "main.h"

I2C_HandleTypeDef hi2c1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
void eeprom_read(uint8_t device_address, uint8_t *address, uint8_t *data, uint8_t size);
void eeprom_write(uint8_t device_address, uint8_t address, uint8_t *data, uint8_t size);


int main(void)
{

  HAL_Init();

  
  SystemClock_Config();

  
  MX_GPIO_Init();
  MX_I2C1_Init();
	uint16_t device_address  = 0b1010;
	uint8_t page = 4;
	device_address = device_address<<3|page;
	uint8_t size = 4;
	uint8_t data_read[size];
	uint8_t address = 0x00;
	eeprom_read(device_address,&address, data_read, size);
	uint8_t data_write[] = "embedded_system_design";
	size = sizeof(data_write);
	eeprom_write(device_address, 0x20, data_write, size);
 
  while (1)
  {
    //do nothing
  }
  
}
void eeprom_read(uint8_t device_address, uint8_t *address, uint8_t *data, uint8_t size){
	uint32_t trials = 4;
	if (HAL_I2C_IsDeviceReady(&hi2c1, 16, trials, 1)){
		device_address = device_address<<1|0;
		HAL_I2C_Master_Transmit(&hi2c1, device_address, address , 1, 1);
		device_address = device_address<<1|1;
		HAL_I2C_Master_Receive(&hi2c1, device_address, data , size, 1);
	}
}
void eeprom_write(uint8_t device_address, uint8_t address, uint8_t *data, uint8_t size){
	uint32_t trials = 4;
	if (HAL_I2C_IsDeviceReady(&hi2c1, 16, trials, 1)){
		device_address = device_address<<1|0;
		HAL_I2C_Master_Transmit(&hi2c1, device_address, &address , 1, 1);
		HAL_I2C_Master_Transmit(&hi2c1, device_address, data , size, 1);
	}
}
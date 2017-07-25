#include "hardware.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart1;

void uart_transmit(char *data, unsigned char size) {
  HAL_UART_Transmit(&huart1, data, size, 0xFFFF);
}

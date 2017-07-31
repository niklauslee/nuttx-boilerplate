#include "hardware.h"
#include "stm32f4xx_hal.h"
#include "jerryscript-port.h"

extern UART_HandleTypeDef huart1;

void uart_transmit(char *data, unsigned char size) {
  HAL_UART_Transmit(&huart1, data, size, 0xFFFF);
}

void jerry_port_fatal (jerry_fatal_code_t code) {
  exit (1);
}

void jerry_port_log (jerry_log_level_t level, const char *format, ...) {
}


bool jerry_port_get_time_zone (jerry_time_zone_t *tz_p) {
}

double jerry_port_get_current_time (void) {
  return 0;
}

void jerry_port_console (const char *format, ...) {
}

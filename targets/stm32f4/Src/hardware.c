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
    if (strlen(format) == 1 && format[0] == 0x0a) { // line feed (\n)
        printf("\r"); // add CR for proper display in serial monitors

        jerry_port_console_printing = false; // not printing anymore...
    }

    if (!jerry_port_console_printing) {
        pc.printf("\33[100D\33[2K");
        jerry_port_console_printing = true;
    }

    va_list args;
    va_start(args, format);
    vfprintf(stdout, format, args);
    va_end(args);

    if (strlen(format) == 1 && format[0] == 0x0a && replInstance) {
        replInstance->printJustHappened();
    }
}

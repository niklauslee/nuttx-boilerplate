#include "console.h"
#include "hardware.h"

char command[COMMAND_LENGTH_MAX];
unsigned char command_idx = 0;

void console_put_char(char ch) {
  command[command_idx] = ch;
  command_idx++;
  uart_transmit(command, command_idx);
}

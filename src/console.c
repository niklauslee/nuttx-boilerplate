#include "console.h"
#include "hardware.h"

#include "event_loop.h"
#include "kameleon_config.h"
#include "jerryscript.h"

char command[MAX_COMMAND_LENGTH];
unsigned char command_idx = 0;

const char prompt[] = ">";
const char newline = '\n';

void console_init() {
  print_to_uart(">", 1);
}

void console_put_char(char ch) {
  if (ch == '\n' || ch == '\r') {
    print_to_uart("\r\n", 2);

    // push a command event to queue.
    io_event_t *event = malloc(sizeof(io_event_t));
    event->type = EVT_COMMAND;
    char *data = malloc(command_idx + 1);
    command[command_idx] = '\0';
    strcpy(data, command);
    event->data = data;
    push_event(event);

    print_to_uart(">", 1);
    command_idx = 0;
  } else {
    command[command_idx] = ch;
    command_idx++;
    uart_transmit(&ch, 1); // echo
  }
}

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "console.h"
#include "hardware.h"
#include "event_loop.h"
#include "interpreter.h"
#include "kameleon_config.h"

/**
 * buffer to store command chars
 */
char buffer[MAX_COMMAND_LENGTH];

/**
 * length of command
 */
unsigned int buffer_length;

/**
 * Indicate whether now in escape sequence
 */
bool in_escape_sequence = false;

/**
 * stores escape sequence
 */
char escape_sequence[3];

/**
 * Length of escape sequence
 */
unsigned int escape_sequence_length = 0;

/**
 * Send a char to the console's serial port
 */
void __putc(char ch) {
  uart_transmit(&ch, 1);
}

/**
 * Send a string (without the last '\0') to the console's serial port
 */
void __puts(char *str) {
  uart_transmit(str, strlen(str));
}

/**
 * Initialize the console
 */
void console_init() {
  buffer_length = 0;
  in_escape_sequence = false;
  escape_sequence_length = 0;
  __puts("\33[2K\r");
  __puts("\r\nWelcome to Kameleon!\r\n");
  __puts("> ");
}

/**
 * Inject a charactor to the console
 */
void console_injectc(char ch) {
  if (in_escape_sequence) {
    // push ch to escape sequence
    escape_sequence[escape_sequence_length] = ch;
    escape_sequence_length++;

    // if ch is last char (a-zA-Z) of escape sequence
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      in_escape_sequence = false;
    }
  } else {
    switch (ch) {
      case '\r': /* carrage return */
        __putc(ch);
        __putc('\n');

        // push a buffer event to queue.
        io_event_t *event = malloc(sizeof(io_event_t));
        event->type = EVT_COMMAND;
        char *data = malloc(buffer_length + 1);
        buffer[buffer_length] = '\0';
        strcpy(data, buffer);
        event->data = data;
        push_event(event);

        __puts("> ");
        buffer_length = 0;
        break;
      case 0x7f: /* backspace */
        if (buffer_length > 0) {
          buffer_length--;
          buffer[buffer_length] = '\0';
          __puts("\033[D\033[K");
        }
        break;
      case 0x1b: /* escape char */
        // __puts("\033[s"); // save current cursor pos
        in_escape_sequence = true;
        escape_sequence_length = 0;
        break;
      default:
        // check buffer overflow
        buffer[buffer_length] = ch;
        buffer_length++;
        __putc(ch);
        break;
    }
  }
}

/**
 * Print a log string to the console
 */
void console_log(char *str) {
  __puts("\33[2K\r"); // set column to 0
  __puts("\33[36m"); // cyan
  __puts(str);
  __puts("\33[0m"); // back to normal color
  __puts("\r\n");
  __puts("> ");
}

/**
 * Print a warning string to the console
 */
void console_warning(char *str) {
  __puts("\33[2K\r"); // set column to 0
  __puts("\33[33m"); // yellow
  __puts(str);
  __puts("\33[0m"); // back to normal color
  __puts("\r\n");
  __puts("> ");
}

/**
 * Print an error string to the console
 */
void console_error(char *str) {
  __puts("\33[2K\r"); // set column to 0
  __puts("\33[31m"); // red
  __puts(str);
  __puts("\33[0m"); // back to normal color
  __puts("\r\n");
  __puts("> ");
}

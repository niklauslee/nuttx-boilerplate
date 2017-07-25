#include "console.h"
#include "hardware.h"

#include "jerryscript.h"

char command[COMMAND_LENGTH_MAX];
unsigned char command_idx = 0;

const char prompt[] = ">";
const char newline = '\n';

void console_init() {
  print_to_uart(">", 1);
}

void console_put_char(char ch) {
  if (ch == '\n') {
    print_to_uart("\n", 1);

    // uart_transmit(command, command_idx);
    jerry_value_t parsed_code = jerry_parse(command, command_idx, false);
    if (!jerry_value_has_error_flag (parsed_code)) {
      jerry_value_t ret_value = jerry_run(parsed_code);
      print_value(ret_value);
      jerry_release_value(ret_value);
    }
    jerry_release_value(parsed_code);

    print_to_uart("\n", 1);
    print_to_uart(">", 1);
    command_idx = 0;
  } else {
    command[command_idx] = ch;
    command_idx++;
    uart_transmit(&ch, 1); // echo
  }
}

void print_to_uart(char data[], unsigned char size) {
  uart_transmit(data, size);
}

void print_value (const jerry_value_t value)
{
  if (jerry_value_is_undefined (value))
  {
    print_to_uart("undefined", 9);
  }
  else if (jerry_value_is_null (value))
  {
    print_to_uart("null", 4);
  }
  else if (jerry_value_is_boolean (value))
  {
    if (jerry_get_boolean_value (value))
    {
      print_to_uart("true", 4);
    }
    else
    {
      print_to_uart("false", 5);
    }
  }
  /* Float value */
  else if (jerry_value_is_number (value))
  {
    print_to_uart("number", 6);
  }
  /* String value */
  else if (jerry_value_is_string (value))
  {
    /* Determining required buffer size */
    jerry_size_t req_sz = jerry_get_string_size (value);
    jerry_char_t str_buf_p[req_sz];

    jerry_string_to_char_buffer (value, str_buf_p, req_sz);
    str_buf_p[req_sz] = '\0';
    print_to_uart(str_buf_p, req_sz);
    // printf ("%s", (const char *) str_buf_p);
  }
  /* Object reference */
  else if (jerry_value_is_object (value))
  {
    print_to_uart("[object]", 8);
  }

  print_to_uart("\n", 1);
}
